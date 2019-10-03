/**
 * \file 	date.c
 * \brief 	Gestion de la date
 * \author 	Loky
 */

#include <toolbox/date.h>
#include <toolbox/memory.h>

#define START_YEAR 1900
#define SIZE_DATE 256
#define NOW "%X"

/**
 * retourne la date courrante
 * \return la date
 */
char* get_date_str()
{
	date_t *tmp = date_t_create_now();
	char* res = tmp->str(tmp, NOW);
	tmp->destroy(tmp);
	return res;
}

static void date_t_init(date_t*);
int date_t_get_year(const date_t*);
int date_t_get_day(const date_t*);
int date_t_get_mounth(const date_t*);
int date_t_get_sec(const date_t*);
int date_t_get_hour(const date_t*);
int date_t_get_min(const date_t*);
_Bool date_t_befor(const struct date_t*, const struct date_t*);
_Bool date_t_after(const struct date_t*, const struct date_t*);
char* date_t_str(const date_t* this, const char*);
void date_t_destroy(date_t*);

static void date_t_init(date_t* this)
{
	this->get_year = date_t_get_year;
	this->get_day = date_t_get_day;
	this->get_mounth = date_t_get_mounth;
	this->get_sec = date_t_get_sec;
	this->get_hour = date_t_get_hour;
	this->get_min = date_t_get_min;
	this->befor = date_t_befor;
	this->after = date_t_after;
	this->str = date_t_str;
	this->destroy = date_t_destroy;
}

void date_t_destroy(date_t* this)
{
	FREE(this);
}

_Bool date_t_befor(const struct date_t* this, const struct date_t* date)
{
	return difftime(this->t, date->t) < 0;
}
_Bool date_t_after(const struct date_t* this, const struct date_t* date)
{

	return difftime(this->t, date->t) > 0;
}

int date_t_get_year(const date_t* this)
{
	return (*localtime(&this->t)).tm_year + START_YEAR;
}
int date_t_get_day(const date_t* this)
{
	return (*localtime(&this->t)).tm_mday;
}
int date_t_get_sec(const date_t* this)
{
	return (*localtime(&this->t)).tm_sec;
}
int date_t_get_mounth(const date_t* this)
{
	return (*localtime(&this->t)).tm_mon + 1;
}
int date_t_get_hour(const date_t* this)
{
	return (*localtime(&this->t)).tm_hour;
}
int date_t_get_min(const date_t* this)
{
	return (*localtime(&this->t)).tm_min;
}

char* date_t_str(const date_t* this, const char* format)
{
	char *res = NULL;
	MALLOC(res,char,SIZE_DATE);
	strftime(res, SIZE_DATE, format, localtime(&this->t));
	return res;
}

/**
 * \brief construit une date initialise a la date courante
 * @return la date
 */
date_t* date_t_create_now()
{
	date_t *this;
	MALLOC(this, date_t, 1);
	date_t_init(this);
	this->t = time(NULL);
	return this;
}

/**
 * Initialise une date
 * @param year l'annee
 * @param mounth le mois
 * @param day le jour
 * @param hour l'heure
 * @param min la minute
 * @param sec la seconde
 * @return la date
 */
date_t* date_t_create(const int year, const int mounth, const int day,
		const int hour, const int min, const int sec)
{
	date_t *this;
	struct tm ti;
	MALLOC(this, date_t, 1);
	date_t_init(this);
	ti.tm_year = year - START_YEAR;
	ti.tm_mon = mounth - 1;
	ti.tm_mday = day;
	ti.tm_hour = hour;
	ti.tm_min = min;
	ti.tm_sec = sec;
	this->t = mktime(&ti);
	return this;
}
