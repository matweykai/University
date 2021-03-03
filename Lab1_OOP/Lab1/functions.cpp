#include "functions.h"

const int BUFFERSIZE = 25;

Teacher* copy(Teacher* base, int size)
{
	Teacher* result = new Teacher[size];
	for (int i = 0; i < size; i++)	//Full copy of teacher's object
	{
		result[i].department = base[i].department;
		result[i].status = base[i].status;
		result[i].fio = new char[strlen(base[i].fio) + 1];
		for (int j = 0; j < strlen(base[i].fio) + 1; j++)
			result[i].fio[j] = base[i].fio[j];
	}
	return result;
}
Teacher* find_by_fio(Teacher* teachers, int size, char* fio)
{
	for (int i = 0; i < size; i++)
		if (!strcmp(teachers[i].fio, fio))
			return &teachers[i];

	return nullptr;
}
void del_teachers(Teacher* teachers, int size)
{
	for (int i = 0; i < size; i++)
		delete teachers[i].fio;
	delete[] teachers;
}
Teacher* filter_by_status(Teacher* base, int size, int status, int* found)
{
	*found = 0;
	for (int i = 0; i < size; i++)
		if (base[i].status == status)
			(*found)++;

	Teacher* result = new Teacher[*found];
	int counter = 0;

	for (int i = 0; i < size; i++)
		if (base[i].status == status)
		{
			//Full copy
			result[counter].department = base[i].department;
			result[counter].status = base[i].status;
			result[counter].fio = new char[strlen(base[i].fio) + 1];
			for (int j = 0; j < strlen(base[i].fio) + 1; j++)
				result[counter].fio[j] = base[i].fio[j];
			counter++;
		}

	return result;
}
Teacher* sort(Teacher* base, int size)
{
	Teacher* result = copy(base, size);
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (strcmp(result[j].fio, result[j + 1].fio) < 0)
			{
				Teacher temp = result[j];
				result[j] = result[j + 1];
				result[j + 1] = temp;
			}
	return result;
}
char* read_str(FILE* source)
{
	char buffer[BUFFERSIZE], * result;
	int str_len, res_str_len = 0, i;

	fgets(buffer, BUFFERSIZE, source);

	str_len = strlen(buffer);
	result = (char*)malloc(str_len * sizeof(char));
	for (i = 0; i < str_len; i++)
		result[i] = buffer[i];

	res_str_len += str_len;

	while (str_len == BUFFERSIZE - 1 && result[str_len - 1] != '\n')
	{
		fgets(buffer, BUFFERSIZE, source);
		str_len = strlen(buffer);
		result = (char*)realloc(result, (res_str_len + str_len) * sizeof(char));

		for (i = 0; i < str_len; i++)
			result[res_str_len + i] = buffer[i];
		res_str_len += str_len;
	}

	result[res_str_len - 1] = '\0';

	return result;
}
bool is_end(FILE* file)
{
	long base = ftell(file);
	fseek(file, 0, SEEK_END);
	bool result = base == ftell(file);
	rewind(file);
	fseek(file, base, SEEK_SET);

	return result;
}