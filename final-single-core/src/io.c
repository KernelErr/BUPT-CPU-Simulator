#include <stdio.h>

short getUserInput() {
    short t = 0;
    printf("in:\n");
    scanf("%hd", &t);
    return t;
}

int printNum(int n) {
    printf("out: %d\n", n);
}