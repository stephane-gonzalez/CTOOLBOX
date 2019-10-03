/**
 * \file 	array.h
 * \brief 	Gestion des tableaux
 * \author 	Loky
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * Nombre d'element du tableau
	 * \param tab le tableau
	 */
#define NB_ELEMENTS(tab) (sizeof(tab)/sizeof*(tab))

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_H_ */
