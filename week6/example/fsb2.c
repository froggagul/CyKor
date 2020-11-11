// gcc -o fsb2 fsb2.c -no-pie
#include <stdio.h>

int main() {
    char buf[100] = { 0, };
    read(0, buf, 100);
    printf(buf);
    return 0;
}
