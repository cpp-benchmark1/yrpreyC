#include <stdio.h>

int main() {
    int a;
    int b;

    printf("Enter a value for 'a': ");
    scanf("%d", &a);

    printf("Enter a value for 'b' (greater than 1): ");
    scanf("%d", &b);

    int c = a * b; // Vulnerabilidade de Integer Overflow
    /*
    If a malicious user provides a value of 'b' greater than 1, 
    they can cause an Integer Overflow and manipulate the program's behavior unpredictably. 
    This can be particularly dangerous if the program relies on these calculations' 
    results to make critical decisions or access sensitive data.
    */
    printf("The product of a and b is %d\n", c);

    return 0;
}
