/**
 * \file	math.h
 * \brief	Outils mathematiques
 * \author	Loky
 */

#ifndef MATH_H_
#define MATH_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdarg.h>
#include <stdlib.h>

void swap( unsigned long ,  unsigned long);

double moyf(const size_t nb, ...);

double moyi(const size_t nb, ...);

/**
 * Retourne le minimum entre deux valeurs
 * \param a premiere valeure
 * \param b seconde valeure
 */
#define MIN(a, b) (a<b ?a:b)

/**
 * Retourne le maximum entre deux valeurs
 * \param a premiere valeure
 * \param b seconde valeure
 */
#define MAX(a, b) (a>=b ?a:b)

/**
 * Retourne le carre de la valeure
 * \param x valeure
 */
#define SQUARE(x) (x*x)

#ifdef __cplusplus
}
#endif

#endif /* MATH_H_ */
