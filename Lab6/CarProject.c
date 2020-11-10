#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 10
#define TRUE 1
#define FALSE 0

typedef struct
{
    char* model;
    char* owner_surname;
    char* owner_name;
    int engine_power;
    int mileage;
}Car;

Car* add_car(struct Car* car_arr, int* size);
char* read_str();
int read_num();
void show_records(Car* car_arr, int size);
void print_line(int length);
Car* copy_car_arr(Car* car_arr, int size);
Car* sort_by_owner_name(Car* car_arr, int size);
void find_cars_by_model(Car* car_arr, int size);
void find_owners_by_mileage(Car* car_arr, int size);


int main()
{
    Car* arr = malloc(sizeof(Car) * 5);
    Car temp_car;
    int r = 5;

    temp_car.engine_power = 12;
    temp_car.mileage = 12;
    temp_car.model = "www";
    temp_car.owner_surname = "www";
    temp_car.owner_name = "b";

    arr[0] = temp_car;
    temp_car.model = "a";
    temp_car.mileage = 10;
    arr[1] = temp_car;
    temp_car.model = "c";
    temp_car.mileage = 100;
    arr[2] = temp_car;
    temp_car.model = "a";
    temp_car.mileage = 120;
    arr[3] = temp_car;
    temp_car.model = "b";
    temp_car.mileage = 23;
    arr[4] = temp_car;

    //arr = add_car(arr, &r);

    show_records(arr, r);
    find_owners_by_mileage(arr, r);

    free(arr);

    return 0;
}

Car* add_car(Car* car_arr, int* size)
{
    Car temp_car;

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

    car_arr = realloc(car_arr, (*(size)+1) * sizeof(Car));
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
void show_records(Car* car_arr, int size)
{
    int i, text_size = 0;

    text_size = printf("Car model        Owner surname         Owner name      Engine power   Mileage\n\n");
    print_line(text_size);

    for (i = 0; i < size; i++)
        printf("%10s%20s%20s%15d%10d\n", car_arr[i].model, car_arr[i].owner_surname, car_arr[i].owner_name, car_arr[i].engine_power, car_arr[i].mileage);
    print_line(text_size);
}
void print_line(int length)
{
    int i;
    for (i = 0; i < length; i++)
        printf("-");
    printf("\n");
}
Car* sort_by_owner_name(Car* car_arr, int size)
{
    int i, j;
    Car temp_car, * result_arr = copy_car_arr(car_arr, size);

    for (i = 0; i < size; i++)
        for (j = 0; j < size - i - 1; j++)
            if (strcmp(result_arr[j + 1].owner_name, result_arr[j].owner_name) < 0)
            {
                temp_car = result_arr[j + 1];
                result_arr[j + 1] = result_arr[j];
                result_arr[j] = temp_car;
            }

    return result_arr;
}
Car* copy_car_arr(Car* car_arr, int size)
{
    Car* new_arr = malloc(size * sizeof(Car));
    int i;

    for (i = 0; i < size; i++)
        new_arr[i] = car_arr[i];

    return new_arr;
}
void find_cars_by_model(Car* car_arr, int size)
{
    char* model;
    int i, found_num = 0;
    Car* temp_car_arr = malloc(size * sizeof(Car));


    printf("Car search\n");
    printf("Enter car model: ");
    model = read_str();

    for (i = 0; i < size; i++)
        if (strcmp(car_arr[i].model, model) == 0)
            temp_car_arr[found_num++] = car_arr[i];

    if (!found_num)
        printf("There is no cars with such model in our list");
    else
    {
        printf("Found cars:\n\n");
        show_records(temp_car_arr, found_num);
    }

    free(temp_car_arr);
}
void find_owners_by_mileage(Car* car_arr, int size)
{
    int i, found = FALSE;
    int mileage = -1;

    printf("Find owners of cars with mileage over some value\n\n");
    printf("Enter minimum mileage: ");

    while (TRUE)
    {
        mileage = read_num();
        if (mileage < 0)
            printf("Mileage can't be negative number. Repeat please: ");
        else
            break;
    }

    for (i = 0; i < size; i++)
        if (car_arr[i].mileage >= mileage)
        {
            found = TRUE;
            printf("%10s  %10s %10s\n", car_arr[i].model, car_arr[i].owner_name, car_arr[i].owner_surname);
        }
    if (!found)
        printf("There is no cars with such mileage in our list\n");
}
