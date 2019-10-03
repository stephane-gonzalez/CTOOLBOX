/**
 * \file	memory.c
 * \brief	Gestion des pointeurs
 * \author	Loky
 */

#include <toolbox/memory.h>

#ifdef COUNT_ALLOC
static unsigned long count_alloc;
static unsigned long count_free;
#endif /* COUNT_ALLOC */

/**
 * Incremente le compteur d'allocation
 */
void incr_alloc()
{
#ifdef COUNT_ALLOC
	count_alloc++;
#endif /* COUNT_ALLOC */
}

/**
 * Incremente le compteur de liberation
 */
void incr_free()
{
#ifdef COUNT_ALLOC
	count_free++;
#endif /* COUNT_ALLOC */
}

/**
 * Affiche l'etat de la memoire
 * @param f flux de sortie
 */
void display_memory_state(FILE * f)
{
#ifdef COUNT_ALLOC
	fprintf(f, "Memory state :\n");
	fprintf(f, "\tAllocate : %i\n", count_alloc);
	fprintf(f, "\tFree : %i\n", count_free);
#else
	fprintf(f, "No memory debugging!\n");
#endif /* COUNT_ALLOC */
	fflush(f);
}
