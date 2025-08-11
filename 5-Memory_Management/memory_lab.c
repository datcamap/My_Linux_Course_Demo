#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t create_stack_overflow_by_recusion(uint32_t depth) {
    char* buffer[depth] __attribute_maybe_unused__;
    printf("Recursion depth: %u\n", depth);    
    return create_stack_overflow_by_recusion(depth + 1);
}

void create_memory_leak(uint32_t heap_size) {
    // Simulate memory leak by allocating memory without freeing it
    void *leak = malloc(heap_size);
    printf("Created %d bytes of leak memory at address 0X%016lX\n", heap_size, (size_t)leak);
}

void create_out_of_memory() {
    // Continuously allocate memory until the system runs out of memory
    while (1) {
        long long* data = (long long *)malloc(sizeof(long long) * 1024 * 1024 * 100);
        if (data == NULL) {
            printf("Out of memory condition reached.\n");
            break;
        }
        else {
            printf("Allocated 100MB at addresss 0X%016lX\n", (size_t)data);
            for (int i = 0; i < 1024 * 1024; i++) {                
                data[i] = 'A'; // Fill the allocated memory to simulate usage
            }
        }
    }
}

typedef enum {
    STACK_OVERFLOW = 0,
    MEMORY_LEAK,
    OUT_OF_MEMORY
} ErrorType;

static const char* command_line_args[] = {
    "stack_overflow",
    "memory_leak",
    "out_of_memory"
};

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], command_line_args[STACK_OVERFLOW]) == 0)) {
        create_stack_overflow_by_recusion(0);
    }
    else if ( argc > 1 && (strcmp(argv[1], command_line_args[MEMORY_LEAK]) == 0)) {
        create_memory_leak(1024 * 1024);
    }
    else if ( argc > 1 && (strcmp(argv[1], command_line_args[OUT_OF_MEMORY]) == 0)) {
        create_out_of_memory();
    }
    else {
        printf("No valid command line argument provided. Please use one of the following:\n stack_overflow\n memory_leak\n out_of_memory\n");
    }
    
    return 0;
}