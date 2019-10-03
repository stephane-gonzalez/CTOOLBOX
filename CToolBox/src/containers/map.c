/**
 * \file 	map.c
 * \brief 	Gestion du map
 * \author 	Loky
 */

#include <stdbool.h>
#include <containers/map.h>
#include <toolbox/memory.h>

struct map_item_t_
{
	pair_t *p;
	map_item_t * left;
	map_item_t * right;
};

static void map_t_init(map_t*);

_Bool map_t_empty(const map_t*);
void map_t_clear(map_t*);
void map_t_destroy(map_t*);
void* map_t_get_value(const map_t*, const void*);
_Bool map_t_has_key(const map_t*, const void*);
void map_t_insert(map_t*, void*, void*);
void map_t_erase(map_t*, const void*);
pair_t** map_t_get_entry(const map_t*);

static void map_t_init(map_t* this)
{
	this->empty = map_t_empty;
	this->clear = map_t_clear;
	this->destroy = map_t_destroy;
	this->get_value = map_t_get_value;
	this->has_key = map_t_has_key;
	this->insert = map_t_insert;
	this->erase = map_t_erase;
	this->get_entry = map_t_get_entry;
}

_Bool map_t_empty(const map_t* this)
{
	return this->size == 0;
}

int get_entry(const map_t* this, const map_item_t * current, pair_t** array,
		int count)
{
	if (current != NULL)
	{
		array[count] = current->p;
		count++;
		count = get_entry(this, current->left, array, count);
		count = get_entry(this, current->right, array, count);
	}
	return count;
}

pair_t** map_t_get_entry(const map_t* this)
{
	pair_t** res;
	MALLOC(res, pair_t*, this->size);
	get_entry(this, this->root, res, 0);
	return res;
}

void clear(map_item_t * current)
{
	if (current != NULL)
	{
		clear(current->left);
		clear(current->right);
		current->p->destroy(current->p);
		FREE(current);
	}
}

void map_t_clear(map_t* this)
{
	this->size=0;
	clear(this->root);
	this->root=NULL;
}
void map_t_destroy(map_t* this)
{
	map_t_clear(this);
	FREE(this);
}

_Bool insert_item(map_t* this, map_item_t * current, map_item_t * insert)
{
	if (current == NULL)
		return true;
	else
	{
		int c = this->compare_to(current->p->first, insert->p->first);
		if (c == -1)
		{
			if (insert_item(this, current->left, insert))
			{
				current->left = insert;
				return false;
			}

		}
		else if (c == 1)
		{
			if (insert_item(this, current->right, insert))
			{
				current->right = insert;
				return false;
			}

		}
	}
	return false;
}

void erase(map_t* this, map_item_t * parent, map_item_t * current,
		const void* key)
{
	int c = this->compare_to(current->p->first, key);
	if (c == 0)
	{
		map_item_t * tmp = current;
		map_item_t * left = current->left;
		map_item_t * right = current->right;
		this->size--;
		tmp->p->destroy(tmp->p);
		if (parent->left == tmp)
			parent->left = NULL;
		else
			parent->right = NULL;
		FREE(tmp);

		if (left != NULL)
			insert_item(this, this->root, left);

		if (right != NULL)
			insert_item(this, this->root, right);
	}
	else
	{
		if (c == -1)
			erase(this, current, current->left, key);
		else if (c == 1)
			erase(this, current, current->right, key);
	}
}

void map_t_erase(map_t* this, const void* key)
{
	if (this->root != NULL)
	{
		int c = this->compare_to(this->root->p->first, key);
		if (c == 0)
		{
			map_item_t * current = this->root;
			this->size--;
			this->root = current->left;
			insert_item(this, this->root, current->right);
			current->p->destroy(current->p);
			FREE(current);
		}
		else
		{
			if (c == -1)
				erase(this, this->root, this->root->left, key);
			else if (c == 1)
				erase(this, this->root, this->root->right, key);
		}
	}
}

void* get_value(const map_t* this, const map_item_t * current, const void* key)
{
	if (current == NULL)
		return NULL;
	else
	{
		int c = this->compare_to(current->p->first, key);
		if (c == 0)
			return current->p->second;
		else if (c == -1)
			return get_value(this, current->left, key);
		else if (c == 1)
			return get_value(this, current->right, key);
	}
	return NULL;
}

void* map_t_get_value(const map_t* this, const void* key)
{
	return get_value(this, this->root, key);
}

_Bool has_key(const map_t* this, const map_item_t * current, const void* key)
{
	if (current == NULL)
		return false;
	else
	{
		int c = this->compare_to(current->p->first, key);
		if (c == 0)
			return true;
		else if (c == -1)
			return has_key(this, current->left, key);
		else if (c == 1)
			return has_key(this, current->right, key);
	}
	return false;
}

_Bool map_t_has_key(const map_t* this, const void* key)
{
	return has_key(this, this->root, key);
}

_Bool insert(map_t* this, map_item_t * current, void* key, void* value)
{
	if (current == NULL)
		return true;
	else
	{
		int c = this->compare_to(current->p->first, key);
		if (c == 0)
		{
			FREE(current->p->second);
			current->p->second = value;
			return false;
		}
		else if (c == -1)
		{
			if (insert(this, current->left, key, value))
			{

				this->size++;
				MALLOC(current->left, map_item_t, 1);
				current->left->left = NULL;
				current->left->right = NULL;
				current->left->p = pair_t_create(key, value);
				return false;
			}

		}
		else if (c == 1)
		{
			if (insert(this, current->right, key, value))
			{
				this->size++;
				MALLOC(current->right, map_item_t, 1);
				current->right->left = NULL;
				current->right->right = NULL;
				current->right->p = pair_t_create(key, value);
				return false;
			}

		}
	}
	return false;
}

void map_t_insert(map_t* this, void* key, void* value)
{

	if (insert(this, this->root, key, value))
	{
		this->size++;
		MALLOC(this->root, map_item_t, 1);
		this->root->left = NULL;
		this->root->right = NULL;
		this->root->p = pair_t_create(key, value);
	}
}

/**
 *	Constructeur de map
 * @param compare_to la fonction de comparaison de la cle
 * @return le map
 */
map_t* map_t_create(compare_to_t compare_to)
{
	map_t *this;
	MALLOC(this, map_t, 1);
	this->root = NULL;
	this->compare_to = compare_to;
	map_t_init(this);
	this->size = 0;
	return this;
}

