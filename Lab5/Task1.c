//--------Task1-------- -

/*

    Для того чтобы закончить вводить текст нужно ввести no с пробелами по бокам: "_no_"( _ - это пробел)

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 50
#define TRUE 1
#define FALSE 0

char** add_str(char** text, char* new_str, int str_num);
char** read_text(int* str_num);
void print_text(char** text, int str_num);
char** get_words(char* str, int* word_num);
char** find_same_words(char* str, int* same_word_num);
void upper_word(char* word);
char** edit_text(char** text, int str_num);
char** center_text(char** text, int str_num);
void work_with_text();
char* find_stop_word(char* str, char* stop_word);


int main()
{
    work_with_text();

    return 0;
}

char** add_str(char** text, char* new_str, int str_num)
{
    int str_len = strlen(new_str);
    text = (char**)realloc(text, (str_num + 1) * sizeof(char*));
    text[str_num] = new_str;
    return text;
}
char** read_text(int* str_num)
{
    char buffer[BUFFERSIZE];
    char* new_str;
    char* no_pointer;
    int n;  //Controlling number of entered symbols
    char no_word[] = "no";
    int continue_flag = 0;  //Flag means the continuing of reading
    char** text;
    int distance = 0;

    new_str = (char*)malloc(sizeof(char));
    text = malloc(sizeof(char*));

    *str_num = 0;
    while (TRUE)
    {
        fgets(buffer, BUFFERSIZE, stdin);
        n = strlen(buffer);

        if (continue_flag)
            new_str = (char*)realloc(new_str, (strlen(new_str) + n) * sizeof(char));
        else
        {
            new_str = (char*)malloc(sizeof(char) * (n + 1));
            new_str[0] = '\0';
        }

        strcat(new_str, buffer);  //Adding buffer symbols in our //string array

        if (n == BUFFERSIZE)
            continue_flag = TRUE;  //Rise flag of continuing
        else
        {
            continue_flag = FALSE;
            no_pointer = find_stop_word(new_str, no_word);  //Finding word "no" in str
            if (no_pointer == NULL)
            {
                text = add_str(text, new_str, *str_num);
                *str_num += 1;
            }
            else
            {
                distance = no_pointer - new_str;
                new_str = (char*)realloc(new_str, (distance + 1) * sizeof(char)); //Saving all before word "no"
                new_str[distance] = '\0';
                text = add_str(text, new_str, *str_num);
                *str_num += 1;
                break;
            }
        }
    }
    return text;
}
void print_text(char** text, int str_num)
{
    int i;

    for (i = 0; i < str_num; i++)
    {
        printf("%s", text[i]);
        printf("\n");
    }
}
char** get_words(char* str, int* word_num)
{

    int word_has_begun = FALSE;
    char* str_iter = str;
    char* word_begin = str;
    char** result_arr = malloc(sizeof(char*));


    while (*str_iter != '\0')
    {
        if (!isalpha(*str_iter))
            str_iter++;
        else
        {
            word_begin = str_iter;
            word_has_begun = TRUE;


            while (isalpha(*str_iter))
                str_iter++;

            if (word_has_begun)
            {
                *(word_num) += 1;
                result_arr = (char**)realloc(result_arr, (*word_num) * sizeof(char*));
                result_arr[*(word_num)-1] = word_begin;
                word_has_begun = FALSE;
            }
        }
    }

    return result_arr;
}
char** find_same_words(char* str, int* same_word_num)
{
    int word_num = 0, has_same, is_right, i, j, sym_index;
    char** words = get_words(str, &word_num);
    char** result_arr = malloc(sizeof(char*));
    *(same_word_num) = 0;

    for (i = 0; i < word_num; i++)
    {
        if (words[i] == NULL)
            continue;
        has_same = FALSE;
        for (j = i + 1; j < word_num; j++)
        {
            if (words[j] == NULL)
                continue;
            is_right = FALSE;
            sym_index = 0;

            while (isalpha(words[i][sym_index]) && isalpha(words[i][sym_index]))
            {
                is_right = TRUE;
                if (words[i][sym_index] != words[j][sym_index])
                {
                    is_right = FALSE;
                    break;
                }
                sym_index++;
            }

            if (is_right)
            {
                *same_word_num += 1;
                result_arr = realloc(result_arr, *(same_word_num) * sizeof(char*));
                result_arr[*(same_word_num)-1] = words[j];
                words[j] = NULL;
                has_same = TRUE;
            }
        }
        if (has_same)
        {
            *(same_word_num) += 1;
            result_arr = realloc(result_arr, *(same_word_num) * sizeof(char*));
            result_arr[*(same_word_num)-1] = words[i];
        }
    }

    return result_arr;
}
void upper_word(char* word)
{
    while (isalpha(*word))
    {
        *word = toupper(*word);
        word++;
    }
}
char** edit_text(char** text, int str_num)
{
    int same_words_num, i, j;
    char** same_words, **result_text;

    for (i = 0; i < str_num; i++)
    {
        same_words = find_same_words(text[i], &same_words_num);
        for (j = 0; j < same_words_num; j++)
            upper_word(same_words[j]);
        free(same_words);
    }

    return center_text(text, str_num);
}
char** center_text(char** text, int str_num)
{
    int max_str_len = strlen(text[0]), i, j, counter = 0;
    char** result_text;

    for (i = 1; i < str_num; i++)
    {
        if (strlen(text[i]) > max_str_len)
            max_str_len = strlen(text[i]);
    }

    result_text = (char*)malloc(str_num * sizeof(char*));

    for (i = 0; i < str_num; i++)
    {
        counter = 0;
        result_text[i] = malloc(sizeof(char) * (max_str_len + 1));
        for (j = 0; j < (max_str_len - strlen(text[i])) / 2; j++)
        {
            result_text[i][j] = ' ';
            counter++;
        }
        for (j = 0; j < strlen(text[i]); j++)
            result_text[i][counter + j] = text[i][j];
        result_text[i][counter + strlen(text[i])] = '\0';
    }

    return result_text;
}
void work_with_text()
{
    char** raw_text, **editted_text;
    int str_num = 0, i;
    char* temp_word;
    int temp_text_pos = 0;

    raw_text = read_text(&str_num);

    editted_text = edit_text(raw_text, str_num);

    printf("\n\n");
    print_text(editted_text, str_num);

    for (i = 0; i < str_num; i++)
    {
        free(raw_text[i]);
        free(editted_text[i]);
    }
    free(raw_text);
    free(editted_text);
}
char* find_stop_word(char* str, char* stop_word)
{
    int has_found = 0;
    char* temp_word_ptr = strstr(str, stop_word);
    char* result_str = NULL;

    while (temp_word_ptr != NULL)
    {
        if (!isalpha(*(temp_word_ptr + strlen(stop_word))) && (temp_word_ptr - str == 0 || !isalpha(*(temp_word_ptr - 1))))
        {
            has_found = 1;
            result_str = temp_word_ptr;
            break;
        }
        temp_word_ptr = strstr(temp_word_ptr + 1, stop_word);
    }

    return temp_word_ptr;
}
