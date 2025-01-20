#include <stdio.h>

int main(int argc, char* argv[]) {
    char a, b;

    a = -128;

    printf("%d\n", (int)a);

    b = a - 1; // Underflow occurs here

    printf("%d\n", (int)b);

    return 0;
}
