#include <math.h>
#include "datatype.h"

int byteToOct(byte* memory) {
    int t = 0;
    for (int i = 0; i < 4; i++) {
        t <<= 8;
        t += *memory;
        memory++;
    }
    return t;
}

short byteToShort(byte* memory) {
    short t = 0;
    for (int i = 0; i < 2; i++) {
        t <<= 8;
        t += *memory;
        memory++;
    }
    return t;
}

int byteToSignedOct(byte* memory) {
    int sign = *memory >> 7;
    int t = byteToShort(memory);
    if (sign == 0) {
        return t;
    } else {
        t &= 32767;
        t -= pow(2, 15);
        return t;
    }
}

int getFirstReg(int n) {
    return n >> 4;
}

int getSecondReg(int n) {
    return n & 15;
}

void writeData(byte* memory, short n) {
    byte low = n;
    byte high = n >> 8;
    *memory = high;
    *(memory + 1) = low;
}