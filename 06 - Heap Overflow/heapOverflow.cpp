#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h> // Para o handler do sinal

#define BUFSIZE 100
#define OVERSIZE 80 /* overflow buf2 by OVERSIZE bytes */

void signal_handler(int signum) {
    if (signum == SIGSEGV) {
        printf("Segmentation fault occurred. Generating memory dump...\n");
        fflush(stdout); // Certifica-se de que todas as saídas são exibidas antes de abortar
        abort(); // Gera um dump de memória
    }
}

int main() {
    int diff;
    char *buf1 = (char *)malloc(BUFSIZE);
    char *buf2 = (char *)malloc(BUFSIZE);

    // Configura o handler do sinal para SIGSEGV (segmentation fault)
    signal(SIGSEGV, signal_handler);

    diff = (intptr_t)buf2 - (intptr_t)buf1;
    printf("buf1 = %p, buf2 = %p, diff = 0x%x bytes\n", (void *)buf1, (void *)buf2, diff);

    memset(buf2, 'A', BUFSIZE - 1);
    buf2[BUFSIZE - 1] = '\0';

    printf("before overflow: buf2 = %s\n", buf2);
    memset(buf1, 'B', (size_t)(diff + OVERSIZE));
    printf("after overflow: buf2 = %s\n", buf2);

    free(buf1);
    free(buf2);

    return 0;
}
