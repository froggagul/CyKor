// gcc -o dsfsa dsfsa.c -no-pie
#include <stdio.h>
#include <stdlib.h>

char buf[100];

void shell() {
    system("/bin/sh");
}

int main() {
    read(0, buf, 100);
    printf(buf);
    read(0, buf, 100);
    printf(buf);

    printf("Bye!");
    return 0;
}