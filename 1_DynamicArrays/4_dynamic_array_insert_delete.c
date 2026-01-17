#include <stdio.h>
#include <stdlib.h>

/*
    Program: Dynamic Array Implementation in C
    Features:
    - Create dynamic array
    - Insert element at any position
    - Delete element from any position
    - Automatic resizing (doubling strategy)
*/

struct DynamicArray
{
    int total_size;   // Total allocated capacity
    int used_size;    // Number of elements currently stored
    int *data;        // Pointer to dynamic memory
};

/* Create a dynamic array */
void createArray(struct DynamicArray *arr, int totalSize, int usedSize)
{
    if (usedSize > totalSize)
    {
        printf("Used size cannot exceed total size\n");
        exit(1);
    }

    arr->total_size = totalSize;
    arr->used_size = usedSize;
    arr->data = (int *)malloc(totalSize * sizeof(int));

    if (arr->data == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

/* Take input values from user */
void setValues(struct DynamicArray *arr)
{
    printf("\nEnter the values:\n");
    for (int i = 0; i < arr->used_size; i++)
    {
        printf("Index %d : ", i);
        scanf("%d", &arr->data[i]);
    }
}

/* Display array elements */
void displayArray(struct DynamicArray *arr)
{
    printf("\nArray elements: ");
    for (int i = 0; i < arr->used_size; i++)
    {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

/* Resize array (double the capacity) */
void resizeArray(struct DynamicArray *arr)
{
    int newSize = 2 * arr->total_size;
    int *temp = (int *)realloc(arr->data, newSize * sizeof(int));

    if (temp == NULL)
    {
        printf("Memory reallocation failed\n");
        free(arr->data);
        exit(1);
    }

    arr->data = temp;
    arr->total_size = newSize;
}

/* Insert element at a given position */
void insertAt(struct DynamicArray *arr, int position, int element)
{
    if (position < 0 || position > arr->used_size)
    {
        printf("Invalid position\n");
        return;
    }

    if (arr->used_size == arr->total_size)
    {
        printf("Resizing array...\n");
        resizeArray(arr);
    }

    for (int i = arr->used_size; i > position; i--)
    {
        arr->data[i] = arr->data[i - 1];
    }

    arr->data[position] = element;
    arr->used_size++;

    printf("After insertion:\n");
    displayArray(arr);
}

/* Delete element from a given position */
void deleteAt(struct DynamicArray *arr, int position)
{
    if (position < 0 || position >= arr->used_size)
    {
        printf("Invalid position\n");
        return;
    }

    for (int i = position; i < arr->used_size - 1; i++)
    {
        arr->data[i] = arr->data[i + 1];
    }

    arr->used_size--;

    printf("After deletion:\n");
    displayArray(arr);
}

int main()
{
    struct DynamicArray arr;
    int initialSize, element, position, choice;

    printf("Enter initial number of elements: ");
    scanf("%d", &initialSize);

    createArray(&arr, initialSize * 2, initialSize);
    setValues(&arr);
    displayArray(&arr);

    while (1)
    {
        printf("\nMenu:");
        printf("\n1. Insert element");
        printf("\n2. Delete element");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element to insert: ");
            scanf("%d", &element);
            printf("Enter position: ");
            scanf("%d", &position);
            insertAt(&arr, position, element);
            break;

        case 2:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            deleteAt(&arr, position);
            break;

        case 3:
            free(arr.data);
            arr.data = NULL;
            exit(0);

        default:
            printf("Invalid choice, try again\n");
        }
    }

    return 0;
}
