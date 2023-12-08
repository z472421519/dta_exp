#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXSIZE 512

void __attribute__((noinline)) hello_hexingbang(int n) {
    printf("\033[31mwo shi Zhangyi, wo jin nian %d sui le!\033[0m\n", n);
}

int main(int argc, char** argv) {  
    char src[MAXSIZE];
    FILE *f;
	unsigned int size, len, value;

    if (argc < 2)
        return -1;

    memset(src, 0, MAXSIZE);

	f = fopen (argv[1], "r");
	
    if (f == NULL)
        return -1;

    len = fread (src, 1, MAXSIZE, f);
    hello_hexingbang(src[3] - '0');

    return 0;
}