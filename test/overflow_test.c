#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define MAXSIZE 32

int main(int argc, char** argv){
    int input, n;
    FILE *f;
    char output[32];
    char in[32];

    for(int i = 0;i < 32;i++)
    {
        in[i] = 'O';
        output[i] = 'T';
    }
    f = fopen (argv[1], "r");
    fread (in, 1, MAXSIZE, f);

    scanf("%d", &input);
    n = input + in[1]; // 2147483647 + 1 (2^31-1)
    n %= 32;
    output[n] = 'X';
    for(int i = 0;i < 32;i++)
        printf("%c",in[i]);
    printf("\n");
    for(int i = 0;i < 32;i++)
        printf("%c",output[i]);
    printf("\n");
    return 0;
}
