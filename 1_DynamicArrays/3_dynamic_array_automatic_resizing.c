#include <stdio.h>
#include <stdlib.h>

/*
     Program: Dynamic Array with Automatic Resizing (Append & Resize)
    Concepts Used:
    - Structures
    - Dynamic Memory Allocation (malloc/realloc/free)
    - Pointers
    - Array resizing by doubling capacity
*/

// Dynamic array structure
struct myArray
{
    int total_size; // Total allocated size
    int used_size;  // Number of elements actually used
    int *data;      // Pointer to dynamically allocated array
};

// Create and initialize dynamic array
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

// Resize the array by doubling its capacity
void resizeArray(struct myArray *arr)
{
    int new_size = arr->total_size * 2;
    // Attempt to resize the existing memory block to hold 'new_size' elements
    // realloc may move the memory block to a new location and returns the new pointer
    int *temp = (int *)realloc(arr->data, new_size * sizeof(int));

    // Check if realloc was successful
    if (temp == NULL)
    {
        // If realloc fails, original memory block is still valid
        // But since we can't resize, free original and exit to avoid memory leak
        printf("Reallocation failed. Exiting.\n");
        free(arr->data);
        exit(1);
    }

    // If realloc succeeded, update the data pointer to the new location
    arr->data = temp;
    // Update the total size capacity to the new resized value
    arr->total_size = new_size;
}

// Append a new element to the dynamic array
void appendElement(struct myArray *arr, int element)
{
    // If array is full, resize before adding new element
    if (arr->used_size == arr->total_size)
    {
        printf("\nSize exceeding total allocated size. Resizing array....\n");
        resizeArray(arr);
    }

    arr->data[arr->used_size] = element;
    arr->used_size++;
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

/* Main Funtion */
int main()
{
    struct myArray arr;
    int i, usersize, newElements, element;

    printf("\nEnter the size of the array : ");
    scanf("%d", &usersize);

    int totalsize = usersize * 2;

    createArray(&arr, totalsize, usersize);

    printf("\nInitialization....");
    setValues(&arr);

    printf("\nTraversal....");
    printValues(&arr);

    printf("\nEnter the number of new elements you want to append : ");
    scanf("%d", &newElements);

    for (i = 0; i < newElements; i++)
    {
        printf("Enter element %d : ", i);
        scanf("%d", &element);
        appendElement(&arr, element);
    }
    printf("\nThe Array after append---");
    printValues(&arr);
    // Free dynamically allocated memory to avoid memory leaks
    free(arr.data);

    return 0;
}
