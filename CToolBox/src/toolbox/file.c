/**
 * \file	file.c
 * \brief	Gestion des fichier
 * \author	Loky
 */

#include <toolbox/file.h>
#include <toolbox/log.h>

/**
 * Lecture dans un fichier
 * \param _buffer buffer
 * \param _file Pointeur sur un FILE
 * \param _size longueur a lire
 * \return le nombre de caracteres lut
 */
size_t FREAD(char *_buffer, FILE *_file, const size_t _size)
{
	size_t n;
	if ((n = fread(_buffer, sizeof(_buffer[0]), _size, _file)) == EOF)
		FATAL("Erreur a la lecture", stderr);
	return n;
}
