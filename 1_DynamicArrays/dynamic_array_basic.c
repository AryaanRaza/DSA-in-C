#include <stdio.h>
#include <stdlib.h>

/*
    Program: Dynamic Array Implementation using Structure
    Concepts Used:
    - Structures
    - Dynamic Memory Allocation (malloc/free)
    - Pointers
*/

struct myArray
{
    int total_size; // Total allocated size
    int used_size;  // Number of elements actually used
    int *data;      // Pointer to dynamically allocated array
};

/* Function to create a dynamic array */
void createArray(struct myArray *arr, int totalSize, int usedSize)
{
    if (usedSize > totalSize)
    {
        printf("Error: Used size cannot be greater than total size.\n");
        exit(1);
    }

    arr->total_size = totalSize;
    arr->used_size = usedSize;
    arr->data = (int *)malloc(totalSize * sizeof(int));

    if (arr->data == NULL)
    {
        printf("Memory allocation falied.\n");
        exit(1);
    }
}

/* Function to set values in the array */
void setValues(struct myArray *arr)
{
    printf("\n  Enter the data for---\n");
    for (int i = 0; i < arr->used_size; i++)
    {
        printf("    Index %d : ", i);
        scanf("%d", &arr->data[i]);
    }
}

/* Function to print array values */
void printValues(struct myArray *arr)
{
    printf("\n  Array elements are:\n   ");
    for (int i = 0; i < arr->used_size; i++)
    {
        printf("%d ", arr->data[i]);
    }
}

/* Main function */
int main()
{
    struct myArray arr;

    createArray(&arr, 10, 5);

    printf("\nInitialization....");
    setValues(&arr);

    printf("\nTransversal....");
    printValues(&arr);

    /* Free dynamically allocated memory */
    free(arr.data);

    return 0;
}