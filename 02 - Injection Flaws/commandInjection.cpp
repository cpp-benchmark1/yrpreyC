#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char directoryName[256];  // Assuming maximum directory name length

    // Prompt the user to enter the name of the directory
    printf("Enter the name of the directory you want to create: ");
    fgets(directoryName, sizeof(directoryName), stdin);
    directoryName[strcspn(directoryName, "\n")] = '\0';  // Remove newline character if present

    // Command to create the directory using the system function
    char command[256];
    sprintf(command, "mkdir %s", directoryName);

    // Execute the command
    int result = system(command);

    // Check if the command was executed successfully
    if (result == 0) {
        printf("Directory '%s' created successfully!\n", directoryName);
    } else {
        fprintf(stderr, "Error creating directory '%s'.\n", directoryName);
    }

    return 0;
}
