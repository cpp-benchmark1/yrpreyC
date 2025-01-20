#include <stdio.h>
#include <stdlib.h>

int main() {
    // Simulating a question from Portuguese to English
    printf("How old are you?\n");
    
    while (1) {
        // Memory leak: Dynamic memory allocation without freeing it later
        int* ptr = (int*)malloc(1000 * sizeof(int)); // Allocating space for 1000 integers

        // No call to free(ptr); is made to free the allocated memory
    }

    return 0;
}
