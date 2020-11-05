--------Task2---------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define M 10
#define RANGE 10

float* create_matrix(int strNum, int colNum);
void initialize_matrix(float* matrix, int strNum, int colNum);
float** create_arr_of_pointers(int size);
float** resize_arr_of_pointers(float** arr, int newSize);
float** find_zero_elements(float* matrix, int strNum, int colNum);
void show_matrix(float* matrix, int strNum, int colNum);
void show_ptr_arr(float** arr, int size);

int main()
{
    float* matrix = create_matrix(N, M);
    float** resultArr = NULL;

    srand(time(NULL));

    initialize_matrix(matrix, N, M);
    show_matrix(matrix, N, M);
    resultArr = find_zero_elements(matrix, N, M);

    free(resultArr);
    free(matrix);

    return 0;
}

float* create_matrix(int strNum, int colNum)
{
    return (float*)malloc(sizeof(float) * strNum * colNum);
}
void initialize_matrix(float* matrix, int strNum, int colNum)
{
    for (int i = 0; i < strNum; i++)
        for (int j = 0; j < colNum; j++)
            *(matrix + i * colNum + j) = (rand() + 100) % RANGE / 10.;
}
float** create_arr_of_pointers(int size)
{
    return (float**)malloc(sizeof(float*) * size);
}
float** resize_arr_of_pointers(float** arr, int newSize)
{
    return (float**)realloc(arr, sizeof(float*) * newSize);
}
float** find_zero_elements(float* matrix, int strNum, int colNum)
{
    int elementCount = 0;
    float** resultArr = create_arr_of_pointers(strNum / 2 * colNum);

    for (int i = strNum / 2; i < strNum; i++)
        for (int j = 0; j < colNum; j++)
        {
            float temp = *(matrix + i * colNum + j);
            if (temp == 0)
                resultArr[elementCount++] = matrix + i * colNum + j;
        }

    resize_arr_of_pointers(resultArr, elementCount);
    show_ptr_arr(resultArr, elementCount);
    return resultArr;
}
void show_matrix(float* matrix, int strNum, int colNum) 
{
    for (int i = 0; i < strNum; i++)
    {
        for (int j = 0; j < colNum; j++)
            printf("%.1f\t", *(matrix + colNum * i + j));
        printf("\n");
    }
}
void show_ptr_arr(float** arr, int size) 
{
    printf("Address:\tNumber:\n\n");
    for (int i = 0; i < size; i++)
        printf("%p\t%f\n", arr + i, *(arr + i));
}