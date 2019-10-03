/**
 * \file	log.h
 * \brief	Gestion du message d'erreur
 * \author	Loky
 */

#ifndef LOG_H_
#define LOG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <toolbox/date.h>

char* get_date_str();

/**
 * Definition des differents type de traces
 */
enum level_t
{
	/**
	 * Affiche toutes les traces
	 */
	ALL = 0,
	/**
	 * Affiche les traces supperrieur ou egal a TRACE
	 */
	TRACE,
	/**
	 * Affiche les traces supperrieur ou egal a INFO
	 */
	INFO,
	/**
	 * Affiche les traces supperrieur ou egal a DEBUG
	 */
	DEBUG,
	/**
	 * Affiche les traces supperrieur ou egal a WARN
	 */
	WARN,
	/**
	 * Affiche les traces supperrieur ou egal a ERROR
	 */
	ERROR,
	/**
	 * Affiche les traces supperrieur ou egal a FATAL
	 */
	FATAL,
	/**
	 * Desactive toutes les traces
	 */
	OFF
};

void set_level(enum level_t);

enum level_t get_level();

/**
 * Message d'erreur
 * \param msg Le message a publier
 * \param stream le flux de sortie
 */
#define ERROR(msg, stream)						\
do												\
{												\
	if(ERROR>=get_level())						\
	{											\
		fprintf(stream,"%s ERROR (%s:%d)  %s() %s\n", get_date_str(), __FILE__, __LINE__, __FUNCTION__, msg);	\
		fflush(stream);							\
	}											\
}while(0)

/**
 * Fatal
 * \param msg Le message a publier
 * \param stream le flux de sortie
 */
#define FATAL(msg, stream)						\
do												\
{      											\
		fprintf(stream,"%s FATAL (%s:%d)  %s() %s\n", get_date_str(), __FILE__, __LINE__, __FUNCTION__, msg);	\
		fflush(stream);							\
		exit(EXIT_FAILURE); 					\
}while(0)

/**
 * Warning
 * \param msg Le message a publier
 * \param stream le flux de sortie
 */
#define WARN(msg, stream)						\
do												\
{												\
	if(WARN>=get_level())						\
	{											\
		fprintf(stream,"%s WARN  (%s:%d)  %s() %s\n", get_date_str(), __FILE__, __LINE__, __FUNCTION__, msg);	\
		fflush(stream);							\
	}											\
}while(0)

/**
 * Warning
 * \param msg Le message a publier
 * \param stream le flux de sortie
 */
#define INFO(msg, stream)						\
do												\
{												\
	if(INFO>=get_level())						\
	{											\
		fprintf(stream,"%s INFO  (%s:%d)  %s() %s\n", get_date_str(), __FILE__, __LINE__, __FUNCTION__, msg);	\
		fflush(stream);							\
	}											\
}while(0)

/**
 * Debug
 * \param msg Le message a publier
 * \param stream le flux de sortie
 */
#define DEBUG(msg, stream) 						\
do												\
{												\
	if(DEBUG>=get_level())						\
	{											\
		fprintf(stream,"%s DEBUG (%s:%d)  %s() %s\n", get_date_str(), __FILE__, __LINE__, __FUNCTION__, msg);	\
		fflush(stream);							\
	}											\
}while(0)

/**
 * Trace
 * \param msg Le message a publier
 * \param stream le flux de sortie
 */
#define TRACE(msg, stream)						\
do												\
{												\
	if(TRACE>=get_level())						\
	{											\
		fprintf(stream,"%s TRACE (%s:%d)  %s() %s\n", get_date_str(), __FILE__, __LINE__, __FUNCTION__, msg);	\
		fflush(stream);							\
	}											\
}while(0)

#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
