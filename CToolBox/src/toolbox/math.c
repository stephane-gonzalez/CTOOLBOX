/**
 * \file	math.c
 * \brief	Outils mathematiques
 * \author	Loky
 */

#include <toolbox/math.h>

/**
 * Echange de valeurs
 * \param _a premiere valeure
 * \param _b seconde valeure
 */
/*
void swap(const void * _a, const void * _b)
{
	void*c = *(void**) _a;
	*(void**) _a = *(void**) _b;
	*(void**) _b = c;
}
*/

void swap(unsigned long _a, unsigned long _b)
{
	void*a;
	void*b;
	void*c ;
	a=_a;
	b=_b;
	c =  a;
	a = b;
	b = c;

	_a=a;
	_b=b;
}

/*
 * Calcule la moyenne a partir de double
 * @param nb nombre de valeure
 * @return la moyenne
 */
double moyf(const size_t nb, ...)
{
	va_list vl;
	double somme = 0;
	int i = 0;
	va_start(vl, nb);
	for (; i < nb; i++)
	{
		double suivant = va_arg(vl, double);
		somme += suivant;
	}
	va_end(vl);
	return somme / nb;
}

/**
 * Calcule la moyenne a partir d'integer
 * @param nb nombre de valeure
 * @return la moyenne
 */
double moyi(const size_t nb, ...)
{
	va_list vl;
	long somme = 0;
	int i = 0;
	va_start(vl, nb);
	for (; i < nb; i++)
	{
		int suivant = va_arg(vl, int);
		somme += suivant;
	}
	va_end(vl);
	return somme / (double) nb;
}
