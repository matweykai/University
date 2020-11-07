#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

#define BUFFERSIZE 10

struct Car
{
    char* model;
    char* owner_surname;
    char* owner_name;
    int engine_power;
    int mileage;
};

struct Car* add_car(struct Car* car_arr, int* size);
char* read_str();
int read_num();
void show_records(struct Car* car_arr, int size);
void print_line(int length);

int main()
{


    return 0;
}

struct Car* add_car(struct Car* car_arr, int* size)
{
    struct Car temp_car;

    printf("Adding information about new car\n\n");
    printf("Enter car model: ");
    temp_car.model = read_str();
    printf("Enter owner surname: ");
    temp_car.owner_surname = read_str();
    printf("Enter owner name: ");
    temp_car.owner_name = read_str();
    printf("Enter engine power: ");
    temp_car.engine_power = read_num();
    printf("Enter mileage: ");
    temp_car.mileage = read_num();

    car_arr = realloc(car_arr, (*(size)+1) * sizeof(struct Car));
    car_arr[*size] = temp_car;
    *size += 1;

    return car_arr;
}
char* read_str()
{
    char buffer[BUFFERSIZE], * result;
    int str_len, res_str_len = 0, i;

    fgets(buffer, BUFFERSIZE, stdin);

    str_len = strlen(buffer);
    result = malloc(str_len * sizeof(char));
    for (i = 0; i < str_len; i++)
        result[i] = buffer[i];

    res_str_len += str_len;

    while (str_len == BUFFERSIZE - 1 && result[str_len - 1] != '\n')
    {
        fgets(buffer, BUFFERSIZE, stdin);
        str_len = strlen(buffer);
        result = realloc(result, (res_str_len + str_len) * sizeof(char));

        for (i = 0; i < str_len; i++)
            result[res_str_len + i] = buffer[i];
        res_str_len += str_len;
    }

    result[res_str_len - 1] = '\0';

    return result;
}
int read_num()
{
    int result;

    while (!scanf_s("%d", &result))
    {
        printf("Enter error. Please repeat\n");
        rewind(stdin);
    }
    rewind(stdin);

    return result;
}
void show_records(struct Car* car_arr, int size)
{
    int i, text_size = 0;

    text_size = printf("Car model\t Owner surname\t Owner name\t Engine power\t\t Mileage\n\n");
    print_line(text_size + 10);

    for (i = 0; i < size; i++)
        printf("%s\t\t%s\t\t%s\t\t%d\t\t%d\n", car_arr[i].model, car_arr[i].owner_surname, car_arr[i].owner_name, car_arr[i].engine_power, car_arr[i].mileage);
    print_line(text_size + 10);
}
void print_line(int length)
{
    int i;
    for (i = 0; i < length; i++)
        printf("-");
    printf("\n");
}
