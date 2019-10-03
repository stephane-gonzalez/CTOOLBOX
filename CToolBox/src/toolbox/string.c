/**
 * \file 	string.c
 * \brief 	Outils pour les chaines de caracteres
 * \author 	Loky
 */

#include <toolbox/string.h>
#include <toolbox/memory.h>
#include <string.h>
#include <stdarg.h>

/**
 * Retourne l'index de la sous chaine de caractere dans la chaine
 * @param cs chaine de caractere
 * @param ct sous chaine de caractere
 * @return index
 */
int str_istr(const char *cs, const char *ct)
{
	int index = -1;

	if (cs != NULL && ct != NULL)
	{
		char *ptr_pos = NULL;

		ptr_pos = strstr(cs, ct);
		if (ptr_pos != NULL)
			index = ptr_pos - cs;
	}
	return index;
}

/**
 * Retourne une partie de la chaine de caractere
 * @param s chaine
 * @param start indice de depart
 * @param end indice de fin
 */
void str_sub(char *s, const size_t start, const size_t end)
{

	if (s != NULL && start <= end && end < strlen(s))
	{
		int i = start, j = 0;
		for (; i <= end; i++, j++)
			if (i != j)
				s[j] = s[i];
		s[j] = '\0';
	}
}

/**
 * Remplace une sous chaine par une autre
 * @param s chaine de base
 * @param search caractere recherche
 * @param replace caractere inserer
 */
void str_replace(char *s, const char search, const char replace)
{
	if (s != NULL && search != replace)
	{
		int i = 0;
		for (; i < strlen(s); i++)
			if (s[i] == search)
				s[i] = replace;
	}
}

/**
 * Nettoye une chaine d'un caractere
 * @param s chaine de base
 * @param search caractere recherche
 */
void str_strip(char *s, const char search)
{
	if (s != NULL)
	{
		int i = 0, j = 0;
		for (; i < strlen(s); i++)
		{
			if (s[i] != search)
			{
				s[j] = s[i];
				j++;
			}
		}
		s[j] = '\0';
	}
}
