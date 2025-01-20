#include <stdio.h>
#include <string.h>
#include <windows.h>

int main() {
    char buffer[6];  // Set a buffer size 5 with space for null terminator
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Sets the text color to red
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    
    
    printf("Enter a maximum of 5 characters: ");
    scanf("%5s", buffer);  // Maximum input of 5 characters to prevent buffer overflow
    printf("Typed characters: %s\n", buffer);

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    
    
    return 0;
}
