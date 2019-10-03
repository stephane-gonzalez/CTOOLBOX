/**
 * \file 	pair.c
 * \brief 	Gestion d'une pair de valeur
 * \author 	Loky
 */
#include <containers/pair.h>
#include <toolbox/memory.h>

static void pair_t_init(pair_t*);
void pair_t_destroy(pair_t*);

static void pair_t_init(pair_t* this)
{
	this->destroy = pair_t_destroy;
}
void pair_t_destroy(pair_t* this)
{
	FREE(this->first);
	FREE(this->second);
	FREE(this);
}

/**
 * Constructeur
 * @param first Le premier element
 * @param second Le second element
 * @return l'element construit
 */
pair_t *pair_t_create(void * first, void * second)
{
	pair_t *this;
	MALLOC(this, pair_t, 1);
	pair_t_init(this);
	this->first = first;
	this->second = second;
	return this;
}
