#include <stdio.h>
#include <string.h>

int main() {
    char user_input[256]; // Assuming maximum input length

    printf("Enter a string without a null terminator: ");
    fgets(user_input, sizeof(user_input), stdin);
    user_input[strcspn(user_input, "\n")] = '\0'; // Remove newline character if present

    // Displaying the last character of the string
    if (user_input[0] != '\0') {
        printf("Last character of the string: %c\n", user_input[strlen(user_input) - 1]);
    } else {
        printf("Empty string entered.\n");
    }

    return 0;
}
