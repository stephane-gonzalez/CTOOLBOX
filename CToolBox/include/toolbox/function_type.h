/**
 * \file 	function_type.h
 * \brief 	Type des fonctions
 * \author 	Loky
 */

#ifndef FUNCTION_TYPE_H_
#define FUNCTION_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdbool.h>
/**
 * Fonction de comparaison
 * \param void* premiere valeure
 * \param void* seconde valeure
 * \return 0 si les deux elements sont egaux<br>
 * 1 si le deuxieme elements est superrieur au premier<br>
 * -1 sinon
 *
 */
typedef int (*compare_to_t)(const void*, const void*);

/**
 * Fonction de comparaison
 * \param void* premiere valeure
 * \param void* seconde valeure
 * \return Vrai si les elements sont egaux Faux sinon
 */
typedef _Bool (*equals_t)(const void*, const void*);

#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_TYPE_H_ */
