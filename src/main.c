#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include "data_structures.c" // include your malloc/free definitions

int main() {
    printf("Initial program break: %p\n", sbrk(0));

    size_t alloc_size = 16; // request 16 bytes

    printf("\nCalling my_malloc(%zu)\n", alloc_size);
    void* user_ptr = my_malloc(alloc_size);
    printf("Returned pointer (user data start): %p\n", user_ptr);

    // Metadata is stored after the user data in your code
    Metadata* meta = (Metadata*)((uintptr_t)user_ptr + alloc_size);
    printf("Metadata address: %p\n", meta);
    printf("Metadata size: %zu\n", meta->size);
    printf("Metadata is_free: %d\n", meta->is_free);

    // Inspect memory byte by byte
    unsigned char* mem = (unsigned char*)user_ptr;
    printf("\nMemory dump of allocated block (user data only):\n");
    for (size_t i = 0; i < alloc_size; i++) {
        printf("%02x ", mem[i]);
    }
    printf("\n");

    printf("\nCurrent program break: %p\n", sbrk(0));

    // Simulate freeing the block
    printf("\nCalling my_free...\n");
    my_free((uintptr_t)user_ptr + alloc_size);
    printf("Metadata is_free after my_free: %d\n", meta->is_free);

    printf("\nFinal program break: %p\n", sbrk(0));

    return 0;
}
