/**
 * \file	file.h
 * \brief 	Gestion des fichier
 * \author 	Loky
 */

#ifndef FILE_H_
#define FILE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <toolbox/log.h>

/**
 * Ouverture d'un fichier
 * \param pFile Pointeur sur un FILE
 * \param nom Nom du fichier a ouvrir
 * \param mode d'ouverture du fichier
 */
#define  FOPEN(pFile, nom, mode)				\
do												\
{												\
	if((pFile = fopen(nom, mode)) == NULL)		\
		FATAL("Ouverture impossible", stderr);	\
}while(0)

/**
 * Fermeture d'un fichier
 * \param pFile Pointeur sur un FILE
 */
#define FCLOSE(pFile)						\
do											\
{											\
  if (fclose(pFile) == EOF)					\
  FATAL("Erreur a la fermeture", stderr);	\
}while(0)

/**
 * Ecriture dans un fichier
 * \param buffer buffer a écrire
 * \param pFile Pointeur sur un FILE
 * \param size longueur a ecrire
 */
#define FWRITE(buffer, pFile, size)					\
do													\
{													\
	if(fwrite(buffer, 1, size, pFile) != size)		\
	FATAL("Erreur a l'ecriture", stderr);			\
}while(0)


#ifdef __cplusplus
}
#endif

#endif /* FILE_H_ */
