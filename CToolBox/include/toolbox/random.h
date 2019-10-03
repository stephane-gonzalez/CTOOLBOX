/**
 * \file	random.h
 * \brief	Gestion de l'alea
 * \author	Loky
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * retourne un double aleatoire compris dans la fourchette [min, max]
	 * \param min valeure minimale
	 * \param max valeure maximale
	 */
#define RAND(min, max) (min + (rand() / (double)RAND_MAX) * (max-min))

#ifdef __cplusplus
}
#endif

#endif /* RANDOM_H_ */
