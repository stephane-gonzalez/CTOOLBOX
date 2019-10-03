/**
 * \file	memory.h
 * \brief	Gestion des pointeurs
 * \author	Loky
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <toolbox/log.h>


void incr_alloc();
void incr_free();
void display_memory_state(FILE *);
/**
 * Allocation de memoire
 * \param ptr pointeur a allouer
 * \param type type a allouer
 * \param nb taille a allouer
 */
#define MALLOC(ptr, type, nb)					\
do												\
{												\
	ptr = (type*)malloc((nb) * sizeof(type)); 	\
	if(ptr == NULL) 							\
		FATAL("Allocation impossible", stderr);	\
	incr_alloc();								\
}while(0)

/**
 * Allocation de memoire initialiser par defaut a NULL
 * \param ptr pointeur a allouer
 * \param type type a allouer
 * \param nb taille a allouer
 */
#define CALLOC(ptr, type, nb)\
do\
{\
	ptr = (type*)calloc((nb) , sizeof(type));\
	if(ptr == NULL)\
		FATAL("Allocation impossible", stderr);\
	incr_alloc();\
}while(0)

/**
 * R�allocation de memoire
 * \param ptr pointeur a allouer
 * \param type type a allouer
 * \param nb taille a allouer
 */
#define REALLOC(ptr, type, nb)\
do\
{\
	type * temp;\
	temp = realloc(ptr, (nb) * sizeof(type));\
	if(temp == NULL)\
	{\
		FREE(ptr);\
		FATAL("Allocation impossible", stderr);\
	}\
	else\
		ptr = temp;\
}while(0)

/**
 * Liberation de la memoire
 * \param ptr pointeur a allouer
 */
#define FREE(ptr)	\
do					\
{					\
	 free(ptr); 	\
     ptr = NULL;	\
     incr_free();	\
}while(0)

#ifdef __cplusplus
}
#endif


#endif /* MEMORY_H_ */
