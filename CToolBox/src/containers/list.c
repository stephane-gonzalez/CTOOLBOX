/**
 * \file 	list.c
 * \brief 	Gestion d'une liste
 * \author 	Loky
 */

#include <stdbool.h>
#include <containers/list.h>
#include <toolbox/memory.h>
#include <toolbox/math.h>

static void list_t_init(list_t*);

_Bool list_t_empty(const list_t*);
void list_t_clear(list_t*);
void list_t_destroy(list_t*);
list_item_t* list_t_push_back(list_t*, void*);
list_item_t* list_t_push_front(list_t*, void*);
void* list_t_get(const list_t*, const size_t);
void* list_t_front(const list_t*);
void* list_t_back(const list_t*);
void list_t_pop_front(list_t*);
void list_t_pop_back(list_t*);
list_item_t* list_t_insert(list_t*, const size_t, void*);
void list_t_erase(list_t*, size_t);
void list_t_reverse(const list_t*);
void list_t_sort(const list_t*, compare_to_t);
void list_t_swap(const list_t*, const list_item_t*, const list_item_t*);
_Bool list_t_contains(const list_t*, const void*, equals_t);


static void list_t_init(list_t* this)
{
	this->clear = list_t_clear;
	this->destroy = list_t_destroy;
	this->empty = list_t_empty;
	this->push_back = list_t_push_back;
	this->push_front = list_t_push_front;
	this->get = list_t_get;
	this->front = list_t_front;
	this->back = list_t_back;
	this->pop_front = list_t_pop_front;
	this->pop_back = list_t_pop_back;
	this->insert = list_t_insert;
	this->reverse = list_t_reverse;
	this->erase = list_t_erase;
	this->swap = list_t_swap;
	this->sort = list_t_sort;
	this->contains = list_t_contains;
}

_Bool list_t_contains(const list_t* this, const void* value, equals_t equals)
{
	list_item_t *item = this->first;
	while (HAS_NEXT_ITEM(item))
	{
		if (equals(item->data, value))
			return true;
		NEXT_ITEM(item);
	}
	return false;
}
void list_t_sort(const list_t* this, compare_to_t compare_to)
{

	list_item_t * it1, *it2;
	void * _i_;
	for (it1 = this->first; it1 != NULL; it1 = it1->next)
		for (it2 = this->last; it2 != it1; it2 = it2->prev)
			if (compare_to(it2->prev->data, it2->data) == -1){
				_i_=(void*)it2->data;
				it2->data =  it2->prev->data;
				it2->prev->data = (list_item_t *)_i_;
			}
				//list_t_swap(this, it2, it2->prev);
				//swap(it2, it2->prev);

}

void list_t_swap(const list_t* this, const list_item_t* first,
		const list_item_t* second)
{
	swap(&first->data, &second->data);

}

void list_t_reverse(const list_t* this)
{
	list_item_t* first = this->first;
	list_item_t* second = this->last;
	int i = 0;
	for (; i < this->size / 2; i++)
	{
		list_item_t *next = first->next;
		list_item_t *prev = second->prev;

		list_t_swap(this, first, second);
		first = next;
		second = prev;
	}

}

void list_t_erase(list_t* this, const size_t position)
{
	if (this->size <= position)
		FATAL("D�passement de la liste", stderr);
	if (position == 0)
		list_t_pop_front(this);
	else if (position == this->size - 1)
		list_t_pop_back(this);
	else if (position < this->size - 1)
	{
		size_t i;
		list_item_t *tmp = this->first;
		for (i = 0; i < position; i++)
			tmp = tmp->next;

		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		FREE(tmp->data);
		FREE(tmp);
		this->size--;
	}
}

list_item_t* list_t_insert(list_t* this, const size_t position, void* value)
{
	list_item_t *item;
	if (this->size < position)
		FATAL("Depassement de la liste", stderr);
	if (position == 0)
		return list_t_push_front(this, value);
	else if (position == this->size)
		return list_t_push_back(this, value);
	else if (position < this->size)
	{
		size_t i;
		list_item_t *tmp = this->first;
		for (i = 0; i < position; i++)
			tmp = tmp->next;

		MALLOC(item, list_item_t, 1);
		item->data = value;
		item->prev = NULL;
		item->next = NULL;

		tmp->prev->next = item;
		item->prev = tmp->prev;

		item->next = tmp;
		tmp->prev = item;

		this->size++;
		return item;
	}
	return NULL;
}

void* list_t_front(const list_t *this)
{
	if (this->size == 0)
		FATAL("La liste est vide", stderr);
	return this->first->data;
}

void list_t_pop_front(list_t *this)
{
	if (this->size > 0)
	{
		list_item_t* tmp = this->first;
		this->first = tmp->next;
		this->size--;
		FREE(tmp->data);
		FREE(tmp);
		if (this->first != NULL)
			this->first->prev = NULL;
	}
}

void list_t_pop_back(list_t *this)
{
	if (this->size > 0)
	{
		list_item_t* tmp = this->last;
		this->last = tmp->prev;

		this->size--;
		FREE(tmp->data);
		FREE(tmp);
		if (this->last != NULL)
			this->last->next = NULL;
	}
}

void* list_t_back(const list_t *this)
{

	if (this->size == 0)
		FATAL("La liste est vide", stderr);
	return this->last->data;
}

void* list_t_get(const list_t* this, const size_t position)
{

	list_item_t *tmp;
	size_t i;
	if (this->size<=0 || this->size <= position)
		FATAL("D�passement de la liste", stderr);
	tmp = this->first;
	for (i = 0; i < position; i++)
		tmp = tmp->next;
	return tmp->data;
}

list_item_t* list_t_push_back(list_t* this, void *value)
{
	list_item_t *item;
	MALLOC(item, list_item_t, 1);
	item->data = value;
	item->prev = NULL;
	item->next = NULL;

	if (this->size == 0)
	{
		this->first = item;
		this->last = item;
		this->size = 1;
	}
	else
	{
		item->prev = this->last;
		this->last->next = item;
		this->last = item;
		this->size++;
	}
	return item;
}

list_item_t* list_t_push_front(list_t* this, void *value)
{
	list_item_t *item;
	MALLOC(item, list_item_t, 1);
	item->data = value;
	item->prev = NULL;
	item->next = NULL;

	if (this->size == 0)
	{
		this->first = item;
		this->last = item;
		this->size = 1;
	}
	else
	{
		item->next = this->first;
		this->first->prev = item;
		this->first = item;
		this->size++;
	}
	return item;
}

_Bool list_t_empty(const list_t* this)
{
	return this->size == 0;
}

/**
 * Initialise la liste
 * \return la liste
 */
list_t* list_t_create()
{
	list_t *this;
	MALLOC(this, list_t, 1);
	list_t_init(this);
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
	return this;
}

void list_t_clear(list_t* this)
{
	list_item_t *tmp2;
	list_item_t *tmp = this->first;
	while (tmp != NULL)
	{
		FREE(tmp->data);
		tmp2 = tmp->next;
		FREE(tmp);
		tmp = tmp2;
	}
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}

void list_t_destroy(list_t* this)
{
	list_t_clear(this);
	FREE(this);
}

