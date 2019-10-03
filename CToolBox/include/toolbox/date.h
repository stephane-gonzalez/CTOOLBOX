/**
 * \file 	date.h
 * \brief 	Gestion de la date
 * \author 	Loky
 */

#ifndef DATE_H_
#define DATE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <time.h>

char* get_date_str();

/**
 * \brief gestion des dates
 */
typedef struct date_t
{
	/**
	 * La date
	 */
	time_t t;

	/**
	 * Destructeur
	 * \param date_t la date
	 */
	void (*destroy)(struct date_t*);

	/**
	 * Retourne l'annee
	 * \param date_t la structure date
	 * \return l'annee
	 */
	int (*get_year)(const struct date_t*);

	/**
	 * Retourne le jour
	 * \param date_t la structure date
	 * \return le jour
	 */
	int (*get_day)(const struct date_t*);

	/**
	 * Retourne le mois
	 * \param date_t la structure date
	 * \return le mois
	 */
	int (*get_mounth)(const struct date_t*);

	/**
	 * Retourne la seconde
	 * \param date_t la structure date
	 * \return la seconde
	 */
	int (*get_sec)(const struct date_t*);

	/**
	 * Retourne l'heure
	 * \param date_t la structure date
	 * \return l'heure
	 */
	int (*get_hour)(const struct date_t*);

	/**
	 * Retourne la minute
	 * \param date_t la structure date
	 * \return la minute
	 */
	int (*get_min)(const struct date_t*);

	/**
	 * Retourne une chaine de caractere definissant la date
	 * \param date_t la structure date
	 * * \param char* le format
	 * \return la chaine
	 */
	char* (*str)(const struct date_t*, const char*);

	/**
	 * Comapraison de deux dates
	 * \param date_t la structure date, puis la date a comparrer
	 * \return vrai si la premiere date et avant la seconde sinon faux
	 */
	_Bool (*befor)(const struct date_t*, const struct date_t*);

	/**
	 * Comapraison de deux dates
	 * \param date_t la structure date, puis la date a comparrer
	 * \return vrai si la premiere date et apres la seconde sinon faux
	 */
	_Bool (*after)(const struct date_t*, const struct date_t*);

} date_t;

date_t* date_t_create_now();

date_t* date_t_create(const int year, const int mounth, const int day,
		const int hour, const int min, const int sec);

#ifdef __cplusplus
}
#endif

#endif /* DATE_H_ */
