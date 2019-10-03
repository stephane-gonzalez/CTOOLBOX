/**
 * \file 	vector.c
 * \brief 	Gestion du vecteur
 * \author 	Loky
 */

#include <stdbool.h>
#include <containers/vector.h>
#include <toolbox/memory.h>
#include <toolbox/math.h>

#define DEFAULT_SIZE 15
#define DEFAULT_INCREMENTAL_SIZE 5

static void vector_t_init(vector_t*);

void vector_t_realloc(vector_t* this);
_Bool vector_t_empty(const vector_t*);
void vector_t_clear(vector_t*);
void vector_t_destroy(vector_t*);
void vector_t_push_back(vector_t*, void*);
void* vector_t_push_front(vector_t*, void*);
void* vector_t_get(const vector_t*, const size_t);
void* vector_t_front(const vector_t*);
void* vector_t_back(const vector_t*);
void vector_t_pop_front(vector_t*);
void vector_t_pop_back(vector_t*);
void vector_t_insert(vector_t*, const size_t, void*);
void vector_t_set(vector_t*, const size_t, void*);
void* vector_t_begin(const vector_t*);
void* vector_t_end(const vector_t*);
void vector_t_erase(vector_t*, size_t);
void vector_t_reverse(const vector_t*);
void vector_t_sort(const vector_t*, compare_to_t);
void vector_t_swap(const vector_t*, const size_t, const size_t);

_Bool vector_t_contains(const vector_t*, const void*, equals_t);

static void vector_t_init(vector_t* this)
{
	this->clear = vector_t_clear;
	this->destroy = vector_t_destroy;
	this->empty = vector_t_empty;
	this->push_back = vector_t_push_back;
	this->get = vector_t_get;
	this->front = vector_t_front;
	this->back = vector_t_back;
	this->pop_back = vector_t_pop_back;
	this->insert = vector_t_insert;
	this->reverse = vector_t_reverse;
	this->erase = vector_t_erase;
	this->swap = vector_t_swap;
	this->set = vector_t_set;
	this->sort = vector_t_sort;
	this->contains = vector_t_contains;
}

_Bool vector_t_contains(const vector_t* this, const void* value,
		equals_t equals)
{
	int i;
	for (i = 0; i < this->size; i++)
		if (equals(this->tab[i], value))
			return true;
	return false;
}
void vector_t_sort(const vector_t* this, compare_to_t compare_to)
{
	qsort(this->tab, this->size, sizeof(void*), compare_to);
}

void vector_t_erase(vector_t* this, const size_t position)
{
	int i;

	if (this->size <= position)
		FATAL("Depassement du vector", stderr);
	FREE(this->tab[position]);
	for (i = position; i < this->size; i++)
		this->tab[i] = this->tab[i + 1];
	this->size--;
}

void vector_t_insert(vector_t* this, const size_t position, void* value)
{
	int i;

	if (this->size < position)
		FATAL("Depassement du vector", stderr);
	if (this->size == this->memory_size)
		vector_t_realloc(this);

	for (i = position; i < this->size; i++)
		this->tab[i + 1] = this->tab[i];
	this->tab[position] = value;
	this->size++;
}

void vector_t_set(vector_t* this, const size_t position, void* value)
{

	if (this->size <= position)
		FATAL("Depassement du vector", stderr);
	this->tab[position] = value;
}

void vector_t_realloc(vector_t* this)
{
	this->memory_size += DEFAULT_INCREMENTAL_SIZE;
	REALLOC(this->tab,void*, this->memory_size);
}
void vector_t_push_back(vector_t* this, void *value)
{
		if (this->size+1 == this->memory_size)
			vector_t_realloc(this);
		this->tab[this->size] = value;
		this->size++;
}

void vector_t_pop_back(vector_t *this)
{
	if (this->size != 0)
	{
		this->size--;
		FREE(this->tab[this->size]);
	}
}

void vector_t_reverse(const vector_t* this)
{
	int i = 0, j = this->size - 1;
	for (; i < this->size / 2; i++, j--)
		vector_t_swap(this, i, j);
}

void vector_t_swap(const vector_t* this, const size_t p1, const size_t p2)
{
	swap(this->tab[p1], this->tab[p2]);
}

void* vector_t_back(const vector_t *this)
{

	if (this->size != 0)
		return this->tab[this->size - 1];
	FATAL("Depassement du vector", stderr);

}

void* vector_t_front(const vector_t *this)
{
	if (this->size != 0)
		return this->tab[0];
	FATAL("Depassement du vector", stderr);
}

void* vector_t_get(const vector_t* this, const size_t position)
{
	if (this->size <= position)
		FATAL("Depassement du vector", stderr);
	return this->tab[position];
}

_Bool vector_t_empty(const vector_t* this)
{
	return this->size == 0;
}

void vector_t_clear(vector_t* this)
{
	int i;
	for (i = 0; i < this->size; i++)
		FREE(this->tab[i]);
	this->size = 0;
	this->memory_size = 0;
}

void vector_t_destroy(vector_t* this)
{
	vector_t_clear(this);
	FREE(this->tab);
	FREE(this);
}

/**
 * Constructeur par defaut
 * @return le vector
 */
vector_t *vector_t_create()
{
	vector_t *this;
	MALLOC(this, vector_t, 1);
	vector_t_init(this);
	this->memory_size = DEFAULT_SIZE;
	MALLOC(this->tab, void*, this->memory_size);
	this->size = 0;
	return this;
}

/**
 *
 * Constructeur par defaut
 * @return le vector
 * @param size La taille par defaut
 */
vector_t *vector_t_create_size(const size_t size)
{
	vector_t *this;
	MALLOC(this, vector_t, 1);
	vector_t_init(this);
	this->size = 0;
	this->memory_size = size;
	CALLOC(this->tab, void*, this->memory_size);
	return this;
}
