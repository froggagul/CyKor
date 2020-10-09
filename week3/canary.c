#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

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

int main(int argc, char* argv[]) {
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
    char Overflow[32];
    if (mprotect(inspector, page_size, PROT_NONE) != 0)
        perror("mprotect() failed!");
    
    printf("Hello world!\n");
    gets(Overflow);
    check(canary);
    return 0;
}