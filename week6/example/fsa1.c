// gcc -o fsa1 fsa1.c -no-pie
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("%p\n", system);
    char buf[100];
    read(0, buf, 100);
    printf(buf);

    printf("/bin/sh");
    return 0;
}