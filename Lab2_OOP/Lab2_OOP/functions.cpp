#include "functions.h"

#define BUFFERSIZE 25

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
int max_size(Teacher* arr)
{
	int result = 0;
	for (int i = 0; i < arr->get_count(); i++)
	{
		int temp_len = strlen(arr[i].get_fullname()->get_name()) + strlen(arr[i].get_fullname()->get_surname()) + strlen( arr[i].get_fullname()->get_second_name());
		if (temp_len > result)
		result = temp_len;
	}
	return result;
}
void print_line(int size, int adding_count = 0)
{
	for (int i = 0; i < size + adding_count; i++)
		cout << "-";
}
int get_word_from_list(list<string>* lst)
{
	char* str = read_str(stdin);

	string entered_word;

	entered_word += str;

	int counter = 1;
	for (int i = 0; i < entered_word.length(); i++)
		entered_word[i] = to_lower(entered_word[i]);

	for (list<string>::iterator iter = lst->begin(); iter != lst->end(); iter++, counter++)
		if (*iter == entered_word)
			return counter;

	return -1;
}
char to_lower(char sym)
{
	if ((int)sym >= 'А' && (int)sym <= 'Я')
		return (char)(sym + 32);
	else
		return tolower(sym);
}
char to_upper(char sym)
{
	if ((int)sym >= 'а' && (int)sym <= 'я')
		return (char)(sym - 32);
	else
		return tolower(sym);
}