#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <errno.h>
#include <inttypes.h>

uint64_t *inspector; // size of carnary is usually 8byte
size_t page_size;

void check(uint64_t canary) {
    mprotect(inspector, page_size, PROT_READ);
    printf("inspector: %ld\ncanary: %ld\n", *inspector, canary);
    if (canary != *inspector) {
        printf("buffer overflow occured\n");
        exit(1);
    }
}

int main(void) {
    // 1. canary - initalization
    int blen;
    // page_size=getpagesize();
    page_size = sysconf(_SC_PAGE_SIZE);
    blen=page_size * 2;
    /*
    ----man mprotect()----
    mprotect() changes protection for the calling process's memory page(s)
    containing any part of the address range in the interval [addr, addr+len-1].
    addr must be aligned to a page boundary
    */
    /*
    malloc might not give you page aligned memory just because you request the size of a page,
    so allocate page aligned memory using posix_memalign()
    */
    if (posix_memalign((void **) &inspector, page_size, blen) != 0)
        perror("Allocation failed!");
    *inspector = rand();
    uint64_t canary = *inspector; // canary get under the buffer(which name is "Overflow")
    // canary-initialization ended

    // 2. get input of code
    char code[32];

    printf("type your code\n");
    gets(code);

    if (mprotect(inspector, page_size, PROT_NONE) != 0)
        perror("mprotect() on inspector failed!");
    // get input of code ended

    // 3. check canary and inspector
    check(canary);

    // 4. NX Bit
    // test if Code implemented on stack is executable
    // nx bit for only on void pointer p
    /* mmap a region for our code */
    size_t len = sizeof(code);

    void *p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (p==MAP_FAILED) {
        perror("mmap() failed");
        return 2;
    }
    /* Copy it in (still not executable) */
    memcpy(p, code, len);

    /* Now make it none-executable/readable/writable (NX-Bit works this way)*/
    if (mprotect(p, len, PROT_NONE) < 0) {
        perror("mprotect failed to mark exec-only");
        return 2;
    }
    // if code executes, it prints return value
    int (*func)(void) = p;
    printf("your code executed and returned %d\n", func());

    return 0;
}