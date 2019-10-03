/**
 * \file 	map.h
 * \brief 	Gestion du map
 * \author 	Loky
 */

#ifndef MAP_H_
#define MAP_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdbool.h>
#include <stdlib.h>
#include <toolbox/function_type.h>
#include <containers/pair.h>

/**
 * Type des item d'un map
 */
typedef struct map_item_t_ map_item_t;

/**
 * \brief Gestion d'un map
 */
typedef struct map_t
{

	/**
	 * Taille du map
	 */
	size_t size;

	/**
	 * Element root
	 */
	map_item_t *root;

	/**
	 * Fonction de comparaison entre les clees
	 */
	compare_to_t compare_to;

	/**
	 * Renseigne si le map est vide
	 * \param map_t le map
	 * \return vrai si il est vide faux sinon
	 */
	_Bool (*empty)(const struct map_t*);

	/**
	 * Vide le map
	 * \param map_t le map
	 */
	void (*clear)(struct map_t*);

	/**
	 * Destructeur
	 * \param map_t le map
	 */
	void (*destroy)(struct map_t*);

	/**
	 * Retourne la valeure correspondant a un clee
	 * \param map_t le map
	 * \param void la clee
	 * \return la valeure
	 */
	void* (*get_value)(const struct map_t*, const void*);

	/**
	 * Renseigne si le map contient la clee
	 * \param map_t le map
	 * \param void la clee
	 * \return Vrai si le ma contient la clee faux sinon
	 */
	_Bool (*has_key)(const struct map_t*, const void*);

	/**
	 * ajoute une valeure au map
	 * \param map_t le map
	 * \param void la clee
	 * \param void la valeure
	 */
	void (*insert)(struct map_t*, void*, void*);

	/**
	 * supprime un element du map
	 * \param map_t le map
	 * \param void la clee
	 */
	void (*erase)(struct map_t*, const void*);

	/**
	 * Retourne un tableau des couple (clee, valeure) du map
	 * \param map_t le map
	 * \return Le tableau des couples
	 */
	pair_t** (*get_entry)(const struct map_t*);
} map_t;

map_t* map_t_create(compare_to_t);

#ifdef __cplusplus
}
#endif
#endif /* MAP_H_ */
