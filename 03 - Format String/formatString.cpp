#include <stdio.h>

int main(void) {
    char buf[16]; // Declare a character array to store user input (vulnerable buffer)
    
    printf("Enter the number of characters (up to 15): ");
    gets(buf); // Read user input into the buf array
    printf("You entered: %s\n", buf);
    
    return 0;
}
