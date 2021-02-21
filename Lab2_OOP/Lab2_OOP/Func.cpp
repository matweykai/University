#pragma once
#include "Func.h"

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
	if ((int)sym >= 'À' && (int)sym <= 'ß')
		return (char)(sym + 32);
	else
		return tolower(sym);
}
char to_upper(char sym)
{
	if ((int)sym >= 'à' && (int)sym <= 'ÿ')
		return (char)(sym - 32);
	else
		return tolower(sym);
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