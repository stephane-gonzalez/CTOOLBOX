/**
 * \file 	pair.h
 * \brief 	Gestion d'une pair de valeur
 * \author 	Loky
 */

#ifndef PAIR_H_
#define PAIR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdbool.h>
/**
 * \brief Gestion de deux elements
 */
typedef struct pair_t
{
	/**
	 * Le premier element
	 */
	void * first;

	/**
	 * Le second element
	 */
	void * second;

	/**
	 * Destructeur
	 * \param pair_t this
	 */
	void (*destroy)(struct pair_t*);
} pair_t;

pair_t *pair_t_create(void * first, void * second);

#ifdef __cplusplus
}
#endif
#endif /* PAIR_H_ */
