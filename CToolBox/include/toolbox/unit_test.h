/**
 * \file 	unit_test.h
 * \brief 	Gestion des test unitaire
 * \author 	Loky
 */

#ifndef UNIT_TEST_H_
#define UNIT_TEST_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <string.h>
#include <toolbox/string.h>

/**
 * Chaine de caractere !=
 */
#define DIFFERENT " != "
/**
 * \brief Type assertion
 */
typedef struct assert_t
{
	/**
	 * Assertion status ok
	 */
	_Bool result_ok;

	/**
	 * Fichier
	 */
	char* file;

	/**
	 * Fonction
	 */
	const char* function;

	/**
	 * Ligne
	 */
	int line;

	/**
	 * Temps d'execution
	 */
	double time;

	/**
	 * message
	 */
	const char* msg;

} assert_t;

/**
 * Prototype de fonction
 */
typedef assert_t* (*test_unit_t)();

void ASSERT_INIT(FILE*);
void ASSERT_EXPORT_RESULT_XML(FILE*);
void ASSERT_RUN(test_unit_t);
assert_t
		* ASSERT_RESULT(const _Bool, char*, const char*, const int, const char*);

/**
 * Execution d'un test
 * \param foo la fonction a executer
 */
#define ASSERT_EXEC(foo)  ASSERT_RUN((test_unit_t)foo)

/**
 * Expression fausse
 * \param b expression
 */
#define ASSERT_FALSE(b)																	\
do																						\
{																						\
	if(b)																				\
		return ASSERT_RESULT(false, __FILE__, __FUNCTION__, __LINE__, "ASSERT_FALSE");	\
}																						\
while(0)

/**
 * Expression vrai
 * \param b expression
 */
#define ASSERT_TRUE(b)																	\
do																						\
{																						\
	if(!(b))																				\
		return ASSERT_RESULT(false, __FILE__, __FUNCTION__, __LINE__, "ASSERT_TRUE");	\
}																						\
while(0)

/**
 * Retourne OK
 */
#define ASSERT_RETURN return ASSERT_RESULT(true, __FILE__ , __FUNCTION__, __LINE__ , "STATUS OK")

/**
 * Compare deux expression
 * \param i1 expression 1
 * \param i2 expression 2
 */
#define ASSERT_EQUALS(i1, i2)															\
do																						\
{																						\
	if(i1!=i2)																			\
		return ASSERT_RESULT(false, __FILE__, __FUNCTION__, __LINE__, "ASSERT_EQUALS");	\
}																						\
while(0)

/**
 * Compare deux nombre decimaux
 * \param d1 float 1
 * \param d2 float 2
 * \param f ecart tolere
 */
#define ASSERT_EQUALS_FLOAT(d1, d2, f)															\
do																								\
{																								\
	if(abs(d1-(d2))>f)																			\
		return ASSERT_RESULT(false, __FILE__, __FUNCTION__, __LINE__, "ASSERT_EQUALS_FLOAT");	\
}																								\
while(0)

/**
 * Compare deux chaines de caractere
 * \param str1 chaine 1
 * \param str2 chaine 2
 */
#define ASSERT_EQUALS_STRING(str1, str2)														\
do																								\
{																								\
	if(strlen(str1)==strlen(str2) && strcmp(str1, str2)!=0)										\
		return ASSERT_RESULT(false, __FILE__, __FUNCTION__, __LINE__, "ASSERT_EQUALS_STRING");	\
}																								\
while(0)

/**
 * Expression non nulle
 * \param v expression
 */
#define ASSERT_NOT_NULL(v)																	\
do																							\
{																							\
	if(v==NULL)																				\
		return ASSERT_RESULT(false, __FILE__, __FUNCTION__, __LINE__, "ASSERT_NOT_NULL");	\
}																							\
while(0)

/**
 * Expression nulle
 * \param v expression
 */
#define ASSERT_NULL(v)																		\
do																							\
{																							\
	if(v!=NULL)																				\
		return ASSERT_RESULT(false, __FILE__, __FUNCTION__, __LINE__, "ASSERT_NULL");		\
}																							\
while(0)

/**
 * Retourne fail
 * \param msg le message
 */
#define FAIL(msg) return ASSERT_RESULT(false, __FILE__, __FUNCTION__, __LINE__, msg)

#ifdef __cplusplus
}
#endif

#endif /* UNIT_TEST_H_ */
