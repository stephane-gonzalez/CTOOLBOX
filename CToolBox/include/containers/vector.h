/**
 * \file 	vector.h
 * \brief 	Gestion du vecteur
 * \author 	LokyS
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdbool.h>
#include <stdlib.h>
#include <toolbox/function_type.h>

/**
 * \brief Gestion d'un vecteur
 */
typedef struct vector_t
{
	/**
	 * Memoire allouee
	 */
	size_t memory_size;

	/**
	 * Nombre d'elements
	 */
	size_t size;

	/**
	 * Tableau
	 */
	void * *tab;

	/**
	 * Renseigne si le vecteur est vide
	 * \param vector_t le vecteur
	 * \return vrai si le vecteur est vide faux sinon
	 */
	_Bool (*empty)(const struct vector_t*);

	/**
	 * Vide le vecteur
	 * \param vector_t le vecteur
	 */
	void (*clear)(struct vector_t*);

	/**
	 * Destructeur
	 * \param vector_t le vecteur
	 */
	void (*destroy)(struct vector_t*);

	/**
	 * Ajoute un element en fin de vecteur
	 * \param vector_t le vecteur
	 */
	void (*push_back)(struct vector_t*, void*);

	/**
	 * retourne le ieme element
	 * \param vector_t le vecteur
	 * \param size_t la position
	 * \return la valeure
	 */
	void* (*get)(const struct vector_t*, const size_t);

	/**
	 * ajoute un element
	 * \param vector_t le vecteur
	 * \param size_t la position
	 * \param void* la donnee
	 */
	void (*insert)(struct vector_t*, const size_t, void*);

	/**
	 * met a jour un element
	 * \param vector_t le vecteur
	 * \param size_t la position
	 * \param void* la donnee
	 */
	void (*set)(struct vector_t*, const size_t, void*);

	/**
	 * Retourne le premier element
	 * \param vector_t le vecteur
	 * \return la valeure
	 */
	void* (*front)(const struct vector_t*);

	/**
	 * Retourne le dernier element
	 * \param vector_t le vecteur
	 * \return la valeure
	 */
	void* (*back)(const struct vector_t*);

	/**
	 * enleve le dernier element
	 * \param vector_t le vecteur
	 */
	void (*pop_back)(struct vector_t*);

	/**
	 * supprime un element
	 * \param vector_t le vecteur
	 * \param la position
	 */
	void (*erase)(struct vector_t*, const size_t);

	/**
	 * Renverse le vecteur
	 * \param vector_t le vecteur
	 */
	void (*reverse)(const struct vector_t*);

	/**
	 * Echange la position de deux elements
	 * \param vector_t le vecteur
	 * \param size_t les positions a echanger
	 */
	void (*swap)(const struct vector_t*, const size_t, const size_t);

	/**
	 * Tri le vecteur
	 * \param vector_t le vecteur
	 * \param compare_to la fonction de comparaison
	 */
	void (*sort)(const struct vector_t*, compare_to_t);

	/**
	 * Renseigne si le vector contient la donn�e
	 * \param vector_t le vecteur
	 * \param void* la donnee
	 * \param equals la fonction de comparaison
	 * \return vrai si il contient la donnee faux sinon
	 */
	_Bool (*contains)(const struct vector_t*, const void*, equals_t);
} vector_t;

vector_t* vector_t_create();
vector_t* vector_t_create_size(const size_t);

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_H_ */
