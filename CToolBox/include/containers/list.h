/**
 * \file 	list.h
 * \brief 	Gestion d'une liste
 * \author 	Loky
 */

#ifndef LIST_H_
#define LIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>
#include <toolbox/function_type.h>
#include <stdbool.h>
/**
 * Renseigne si il y a un item suivant
 * \param item item courrant
 */
#define HAS_NEXT_ITEM(item) (item!=NULL?true:false)

/**
 * Va a l'item suivant
 * \param item item courrant
 */
#define NEXT_ITEM(item) item=item->next

/**
 * Renseigne si il y a un item precedant
 * \param item item courrant
 */
#define HAS_PREVIOUS_ITEM(item) (item->prev!=NULL?TRUE:FALSE)

/**
 * Va a l'item precedant
 * \param item item courrant
 */
#define PREVIOUS_ITEM(item) item=item->prev

/**
 * \brief Gestion des item de la liste
 */
typedef struct list_item_t
{
	/**
	 * Item suivant
	 */
	struct list_item_t *next;

	/**
	 * Item precedant
	 */
	struct list_item_t *prev;

	/**
	 * Donnee
	 */
	void * data;
} list_item_t;

/**
 * \brief Gestion d'une liste
 */
typedef struct list_t
{
	/**
	 * Premier element de la liste
	 */
	list_item_t *first;

	/**
	 * Derniere element de la liste
	 */
	list_item_t *last;

	/**
	 * Taille de la liste
	 */
	size_t size;

	/**
	 * Renseigne si la liste est vide
	 * \param list_t la liste
	 * \return vrai si la liste est vide faux sinon
	 */
	_Bool (*empty)(const struct list_t*);

	/**
	 * Vide la liste
	 * \param list_t la liste
	 */
	void (*clear)(struct list_t*);

	/**
	 * Destructeur
	 * \param list_t la liste
	 */
	void (*destroy)(struct list_t*);

	/**
	 * Ajoute un element en fin de liste
	 * \param list_t la liste
	 * \param void* l'element
	 * \return L'element ajoute
	 */
	list_item_t* (*push_back)(struct list_t*, void*);

	/**
	 * Ajoute un element en debut de liste
	 * \param list_t la liste
	 * \param void* l'element
	 * \return L'element ajoute
	 */
	list_item_t* (*push_front)(struct list_t*, void*);

	/**
	 * retourne le ieme element
	 * \param list_t la liste
	 * \param size_t la position de l'element
	 * \return L'element
	 */
	void* (*get)(const struct list_t*, const size_t);

	/**
	 * Insert un element a un position
	 * \param list_t la liste
	 * \param size_t la position de l'element
	 * \param void*  L'element
	 * \return L'element ajoute
	 */
	list_item_t* (*insert)(struct list_t*, const size_t, void*);

	/**
	 * retourne le premier element
	 * \param list_t la liste
	 * \return L'element
	 */
	void* (*front)(const struct list_t*);

	/**
	 * retourne le dernier element
	 * \param list_t la liste
	 * \return L'element
	 */
	void* (*back)(const struct list_t*);

	/**
	 * retire l'element en debut de liste
	 * \param list_t la liste
	 * \return L'element retiré
	 */
	void (*pop_front)(struct list_t*);

	/**
	 * retire l'element en fin de liste
	 * \param list_t la liste
	 * \return L'element retiré
	 */
	void (*pop_back)(struct list_t*);

	/**
	 * Supprime un element a une position
	 * \param list_t la liste
	 * \param size_t la position de l'element
	 */
	void (*erase)(struct list_t*, const size_t);

	/**
	 * Renverse l'ordre de la liste
	 * \param list_t la liste
	 */
	void (*reverse)(const struct list_t*);

	/**
	 * Echange la position de deux elements
	 * \param list_t la liste
	 * \param list_item_t les elements a echanger
	 */
	void (*swap)(const struct list_t*, const list_item_t*, const list_item_t*);

	/**
	 * Tri une liste
	 * \param list_t la liste
	 * \param compare_to la fonction de comparaison
	 */
	void (*sort)(const struct list_t*, compare_to_t);

	/**
	 * Renseigne si la liste contient la donnée
	 * \param list_t la liste
	 * \param void* la donnee
	 * \param equals la fonction de comparaison
	 * \return vrai si il contient la donnee faux sinon
	 */
	_Bool (*contains)(const struct list_t*, const void*, equals_t);

} list_t;

list_t* list_t_create();

#ifdef __cplusplus
}
#endif

#endif /* LIST_H_ */
