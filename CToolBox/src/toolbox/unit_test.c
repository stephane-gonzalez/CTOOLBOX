/**
 * \file 	unit_test.c
 * \brief 	Gestion des tests unitaire
 * \author 	Loky
 */

#include <toolbox/unit_test.h>
#include <toolbox/file.h>
#include <toolbox/memory.h>
#include <containers/vector.h>
#include <stdbool.h>

/**
 * Construit une assertion
 * @param result_ok Vrai si le test est pass� avec succes
 * @param file Fichier du test
 * @param function Fonction du test
 * @param line Ligne du test
 * @param msg Message
 * @return L'assertion
 */
assert_t* ASSERT_RESULT(const _Bool result_ok, char* file,
		const char* function, const int line, const char* msg)
{
	assert_t* res;
	int pos = 0;
	MALLOC(res, assert_t, 1);
	res->result_ok = result_ok;
	MALLOC(res->file, char, strlen(file));
	strcpy(res->file, file);
	pos = str_istr(res->file, ".c");
	if (pos != -1)
		str_sub_start(res->file, pos);
	pos = str_istr(res->file, ".cpp");
	if (pos != -1)
		str_sub_start(res->file, pos);
	str_strip(res->file, '.');
	str_replace(res->file, '/', '.');
	str_replace(res->file, '\\', '.');
	;
	if (res->file[0] == '.' && strlen(res->file) > 0)
		str_sub_end(res->file, 1);

	res->line = line;
	res->function = function;
	res->msg = msg;
	return res;
}

static FILE* stream;

static vector_t *vector;

/**
 * Initialisation
 * @param _stream flux
 */
void ASSERT_INIT(FILE * _stream)
{
	stream = _stream;
	vector = vector_t_create();
}

/**
 * Export du resultat au format xml
 * @param _stream le fichier
 */
void ASSERT_EXPORT_RESULT_XML(FILE * _stream)
{

	int i = 0;
	int failures = 0;
	double time = 0;
	for (; i < vector->size; i++)
	{
		assert_t *assert = vector->get(vector, i);
		if (!assert->result_ok)
			failures++;
		time += assert->time;
	}
	fprintf(
			_stream,
			"<testsuite errors=\"0\" failures=\"%d\" tests=\"%d\" time=\"%f\">\n",
			failures, vector->size, time);

	for (i = 0; i < vector->size; i++)
	{
		assert_t *assert = vector->get(vector, i);
		if (assert->result_ok)
			fprintf(_stream,
					"\t<testcase classname=\"%s\" name=\"%s\" time=\"%f\"/>\n",
					assert->file, assert->function, assert->time);
		else
		{

			fprintf(_stream,
					"\t<testcase classname=\"%s\" name=\"%s\" time=\"%f\">\n",
					assert->file, assert->function, assert->time);

			fprintf(_stream, "\t\t<failure type=\"%s\">\n", assert->msg);
			fprintf(_stream, "\t\t\tFAILURE : %s:%d %s() \"%s\" in %.3fms\n",
					assert->file, assert->line, assert->function, assert->msg,
					assert->time);
			fprintf(_stream, "\t\t</failure>\n", assert->msg);
			fprintf(_stream, "\t</testcase>\n");
		}
	}
	fprintf(_stream, "</testsuite>\n");
	fflush(_stream);
	vector->destroy(vector);
}

/**
 * Lancement d'un test
 * @param foo Fonction a executer
 */
void ASSERT_RUN(test_unit_t foo)
{
	clock_t start = clock();

	assert_t *res = foo();
	res->time = (clock() - start) / (double) CLOCKS_PER_SEC;
	vector->push_back(vector, res);

	if (res->result_ok)
		fprintf(stream, "RUN : %s %s() => OK in %.3fms\n", res->file,
				res->function, res->time);
	else
		fprintf(stream, "FAILURE : %s:%d %s() \"%s\" in %.3fms\n", res->file,
				res->line, res->function, res->msg, res->time);
	fflush(stream);
}

