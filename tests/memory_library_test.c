// tests/memory_library_test.c
#include <stdio.h>
#include <string.h>
#include "../header/my_library.h"  // adjust path if needed

int main() {
    printf("Testing halloc and free_pointer...\n");

    // Allocate memory for an integer
    int* num = (int*) halloc(sizeof(int));
    if (num == NULL) {
        printf("Allocation failed!\n");
        return 1;
    }
    *num = 42;
    printf("Allocated int: %d\n", *num);

    // Allocate memory for a string
    char* str = (char*) halloc(20 * sizeof(char));
    if (str == NULL) {
        printf("Allocation failed!\n");
        return 1;
    }
    strcpy(str, "Hello, World!");
    printf("Allocated string: %s\n", str);

    // Free the allocated memory
    free_pointer(num);
    free_pointer(str);

    printf("Memory successfully freed.\n");
    return 0;
}
