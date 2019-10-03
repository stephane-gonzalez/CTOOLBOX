/**
 * \file 	log.c
 * \brief	Gestion du message d'erreur
 * \author	Loky
 */

#include <toolbox/log.h>

static enum level_t level = ALL;

/**
 * Met a jour le niveau de trace
 * @param l le niveau
 */
void set_level(enum level_t l)
{
	level = l;
}

/**
 * Retourne le niveau de traces a afficher
 * @return le niveau
 */
enum level_t get_level()
{
	return level;
}

