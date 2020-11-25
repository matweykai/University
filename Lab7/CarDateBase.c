#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define BUFFERSIZE 10
#define TRUE 1
#define FALSE 0

typedef struct
{
    char* name;
    char* surname;
}Fio;

typedef struct
{
    int day;
    char* month;
    int year;
}Date;

typedef struct
{
    char* model;
    Fio fio;
    Date service_date;
    int engine_power;
    int mileage;
}Car;

Car* add_car(struct Car* car_arr, int* size);
char* read_str(FILE*);
int read_num();
void show_records(Car* car_arr, int size);
void print_line(int length);
Car* copy_car_arr(Car* car_arr, int size);
Car* sort_by_owner_name(Car* car_arr, int size);
void find_cars_by_model(Car* car_arr, int size);
void find_owners_by_mileage(Car* car_arr, int size);
Car* start_menu(Car* car_arr, int* size);
Date read_date();
int month_in_int(char* word);
Date current_date();
void free_memory(Car* car_arr, int size);
int dist_bet_dates(Date date1, Date date2);
void find_cars_with_service_limit(Car* car_arr, int size);
void save_object_state(FILE* file, Car car);
Car* get_object(FILE* file);
Car* download_database(FILE* file, int* size);
void save_database(FILE* file, Car* car_arr, int size);


int main()
{
    /*system("mode con cols=100");
    Car* car_arr = malloc(sizeof(Car));
    int size = 0;

    car_arr = start_menu(car_arr, &size);

    free_memory(car_arr, size);*/
    FILE* file = fopen("test.bin", "a+");
    int size;
    Car* car_arr = download_database(file, &size);
    show_records(car_arr, size);
    free_memory(car_arr, size);
    fclose(file);
    return 0;
}
Car* start_menu(Car* car_arr, int* size)
{
    char pressed_button;
    int exit = FALSE;

    printf("This is something like car database. You are welcome :)\n");
    printf("Press any key");
    _getch();

    while (!exit)
    {
        system("cls");
        printf("NUM - FUNCTION\n\n");
        printf(" 1  - Add new record\n");
        printf(" 2  - Show all records\n");
        printf(" 3  - Find owners by mileage of his car\n");
        printf(" 4  - Find cars by model\n");
        printf(" 5  - Find cars with service date older than 18 months\n");
        printf(" 6  - Leave the program\n");
        printf("\nEnter function number - ");
        pressed_button = _getch();

        system("cls");

        switch (pressed_button)
        {
        case '1':
            car_arr = add_car(car_arr, size);
            break;
        case '2':
            show_records(car_arr, *size);
            break;
        case '3':
            find_owners_by_mileage(car_arr, *size);
            break;
        case '4':
            find_cars_by_model(car_arr, *size);
            break;
        case '5':
            find_cars_with_service_limit(car_arr, *size);
            break;
        case '6':
            exit = TRUE;
            continue;
            break;
        default:
            printf("Wrong enter, please repeat...\n Press any key");
            _getch();
            continue;
            break;
        }
        printf("Press any key to return to menu");
        _getch();
    }
    return car_arr;
}
Car* add_car(Car* car_arr, int* size)
{
    Car temp_car;
    int temp_mileage, temp_engine_power;

    printf("Adding information about new car\n\n");
    printf("Enter car model: ");
    temp_car.model = read_str(stdin);
    printf("Enter owner surname: ");
    temp_car.fio.surname = read_str(stdin);
    printf("Enter owner name: ");
    temp_car.fio.name = read_str(stdin);
    printf("Enter engine power: ");
    while (TRUE)
    {
        temp_engine_power = read_num();
        if (temp_engine_power < 0)
            printf("Engine power can't be negative number. Repeat please: ");
        else
            break;
    }
    temp_car.engine_power = temp_engine_power;
    printf("Enter mileage: ");
    while (TRUE)
    {
        temp_mileage = read_num();
        if (temp_mileage < 0)
            printf("Mileage can't be negative number. Repeat please: ");
        else
            break;
    }
    temp_car.mileage = temp_mileage;
    printf("Adding date of last service\n");
    temp_car.service_date = read_date();

    car_arr = realloc(car_arr, (*(size)+1) * sizeof(Car));
    car_arr[*size] = temp_car;
    *size += 1;

    return car_arr;
}
char* read_str(FILE *source)
{
    char buffer[BUFFERSIZE], * result;
    int str_len, res_str_len = 0, i;

    fgets(buffer, BUFFERSIZE, source);

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
void show_records(Car* car_arr, int size) //Updated
{
    int i, text_size = 0;

    text_size = printf("Car model        Owner surname         Owner name      Engine power   Mileage   Service Date\n\n");
    print_line(text_size);

    for (i = 0; i < size; i++)
        printf("%10s%20s%20s%15d%10d    %d %s %d\n", car_arr[i].model, car_arr[i].fio.surname, car_arr[i].fio.name, car_arr[i].engine_power, car_arr[i].mileage, car_arr[i].service_date.day, car_arr[i].service_date.month, car_arr[i].service_date.year);
    print_line(text_size);
}
void print_line(int length)
{
    int i;
    for (i = 0; i < length; i++)
        printf("-");
    printf("\n");
}
Car* sort_by_owner_name(Car* car_arr, int size) //Updated
{
    int i, j;
    Car temp_car, * result_arr = copy_car_arr(car_arr, size);

    for (i = 0; i < size; i++)
        for (j = 0; j < size - i - 1; j++)
            if (strcmp(result_arr[j + 1].fio.name, result_arr[j].fio.name) < 0)
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
    model = read_str(stdin);

    for (i = 0; i < size; i++)
        if (strcmp(car_arr[i].model, model) == 0)
            temp_car_arr[found_num++] = car_arr[i];

    if (!found_num)
        printf("There is no cars with such model in our list\n");
    else
    {
        printf("Found cars:\n\n");
        show_records(temp_car_arr, found_num);
    }

    free(temp_car_arr);
    free(model);
}
void find_owners_by_mileage(Car* car_arr, int size) //Updated
{
    int i, found_num = 0, mileage = -1;
    Car* temp_car_arr = malloc(sizeof(Car) * size), * sorted_car_arr = malloc(sizeof(Car) * size);

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
            temp_car_arr[found_num].fio.name = car_arr[i].fio.name;
            temp_car_arr[found_num].fio.surname = car_arr[i].fio.surname;
            found_num++;
        }
    if (!found_num)
        printf("There is no cars with such mileage in our list\n");
    else
    {
        i = printf("          Owner name        Owner surname\n");
        print_line(i);
        free(sorted_car_arr);
        sorted_car_arr = sort_by_owner_name(temp_car_arr, found_num);
        for (i = 0; i < found_num; i++)
            printf("%20s %20s\n", sorted_car_arr[i].fio.name, sorted_car_arr[i].fio.surname);
    }
    free(sorted_car_arr);
    free(temp_car_arr);
}
Date read_date()
{
    int day, year;
    char* month;
    Date result;

    printf("Enter day: ");
    while (TRUE)
    {
        day = read_num();
        if (day < 0 || day > 31)
            printf("Wrong day, it can't be more than 31 and less than 1. Repeat please: ");
        else
            break;
    }
    printf("Enter month: ");
    while (TRUE)
    {
        month = read_str(stdin);
        if (month_in_int(month) == -1)
        {
            printf("Enter is wrong. Repeat enter: ");
            free(month);
        }
        else
            break;
    }
    printf("Enter year: ");
    while (TRUE)
    {
        year = read_num();
        if (year < 0)
            printf("Year can't be negative number. Repeat enter: ");
        else
            break;
    }

    result.day = day;
    result.month = month;
    result.year = year;

    return result;
}
int month_in_int(char* word)
{
    int i;

    for (i = 0; i < strlen(word); i++)
        word[i] = tolower(word[i]);

    if (!strcmp(word, "january"))
        return 1;
    if (!strcmp(word, "february"))
        return 2;
    if (!strcmp(word, "march"))
        return 3;
    if (!strcmp(word, "april"))
        return 4;
    if (!strcmp(word, "may"))
        return 5;
    if (!strcmp(word, "june"))
        return 6;
    if (!strcmp(word, "july"))
        return 7;
    if (!strcmp(word, "august"))
        return 8;
    if (!strcmp(word, "september"))
        return 9;
    if (!strcmp(word, "october"))
        return 10;
    if (!strcmp(word, "november"))
        return 11;
    if (!strcmp(word, "december"))
        return 12;

    return -1;
}
Date current_date()
{
    time_t temp = time(NULL);
    struct tm* current_date = localtime(&temp);
    Date result;
    char* month = "";
    int i;

    switch (current_date->tm_mon)
    {
    case 0:
        month = "january";
        break;
    case 1:
        month = "february";
        break;
    case 2:
        month = "march";
        break;
    case 3:
        month = "april";
        break;
    case 4:
        month = "may";
        break;
    case 5:
        month = "june";
        break;
    case 6:
        month = "july";
        break;
    case 7:
        month = "august";
        break;
    case 8:
        month = "september";
        break;
    case 9:
        month = "october";
        break;
    case 10:
        month = "november";
        break;
    case 11:
        month = "december";
        break;
    }

    result.day = current_date->tm_mday;
    result.year = 1900 + current_date->tm_year;
    result.month = malloc(sizeof(char) * strlen(month) + 1);
    for (i = 0; i <= strlen(month); i++)
        result.month[i] = month[i];

    return result;
}
void free_memory(Car* car_arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(car_arr[i].fio.name);
        free(car_arr[i].fio.surname);
        free(car_arr[i].service_date.month);
        free(car_arr[i].model);
    }
    free(car_arr);
}
int dist_bet_dates(Date date1, Date date2)
{
    int month_1 = month_in_int(date1.month), month_2 = month_in_int(date2.month);

    return abs((date1.year * 12 + month_1) - (date2.year * 12 + month_2));
}
void find_cars_with_service_limit(Car* car_arr, int size)
{
    Car* found_cars = malloc(sizeof(Car) * size);
    int i, found_cars_num = 0;

    for (i = 0; i < size; i++)
        if (dist_bet_dates(current_date(), car_arr[i].service_date) >= 18)
            found_cars[found_cars_num++] = car_arr[i];

    printf("Cars with service date older than 18 months: \n\n");
    show_records(found_cars, found_cars_num);

    free(found_cars);
}
void save_object_state(FILE *file, Car car)
{
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s\n%s\n%s\n%d\n%s\n%d\n%d\n%d\n",
        car.model, car.fio.name, car.fio.surname, car.service_date.day,
        car.service_date.month, car.service_date.year, car.engine_power, car.mileage);
}
Car* get_object(FILE *file)
{
    Car *result_object;

    if (feof(file))
        return NULL;

    result_object = malloc(sizeof(Car));
    result_object->model = read_str(file);
    result_object->fio.name = read_str(file);
    result_object->fio.surname = read_str(file);
    fscanf(file, "%d\n", &result_object->service_date.day);
    result_object->service_date.month = read_str(file);
    fscanf(file, "%d\n", &result_object->service_date.year);
    fscanf(file, "%d\n", &result_object->engine_power);
    fscanf(file, "%d\n", &result_object->mileage);

    return result_object;
}
Car* download_database(FILE* file,int *size)
{
    Car* result_arr = NULL;
    Car* temp_car;
    *size = 0;

    while (TRUE)
    {
        temp_car = get_object(file);
        if (temp_car == NULL)
            break;
        else
        {
            result_arr = realloc(result_arr, sizeof(Car) * (*size + 1));
            result_arr[*size] = *temp_car;
            *size += 1;
        }
    }

    return result_arr;
}
void save_database(FILE *file, Car* car_arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
        save_object_state(file, car_arr[i]);
}
