#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXSIZE 512

int vulfun1(char input[]){
    int BUFF[10];
    char input1[10];
    memset(BUFF, 0, sizeof(BUFF));

    strcpy(input1, input);
    BUFF[0] %= 20;
    BUFF[BUFF[0]] = 10;
    return 0;
}
int main(int argc, char** argv) {
    int n;
    FILE *f;
    char input[MAXSIZE];
	f = fopen (argv[1], "r");
    fread (input, 1, MAXSIZE, f);
    vulfun1(input);
    return 0;
}
