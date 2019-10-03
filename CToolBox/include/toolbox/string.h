/**
 * \file 	string.h
 * \brief 	Outils pour les chaines de caracteres
 * \author 	Loky
 */

#ifndef STRING_H_
#define STRING_H_

#ifdef __cplusplus

extern "C"
{
#endif

#include <stdlib.h>

/**
 * Retourne le debut de la chaine de caractere
 * @param s chaine
 * @param end indice de fin
 */
#define str_sub_start(s, end) str_sub(s, 0, end)

/**
 * Retourne la fin de la chaine de caractere
 * @param s chaine
 * @param start indice de debut
 */
#define str_sub_end(s, start) str_sub(s, start, strlen(s)-1)

int str_istr(const char *, const char *);

void str_sub(char *, const size_t, const size_t);

void str_replace(char *, const char, const char);

void str_strip(char *, const char);

#ifdef __cplusplus
}
#endif

#endif /* STRING_H_ */
