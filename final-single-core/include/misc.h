#include "datatype.h"

#ifndef _MISC_H_
#define _MISC_H_

int byteToOct(byte* memory);
short byteToShort(byte* memory);
int byteToSignedOct(byte* memory);
int getFirstReg(int n);
int getSecondReg(int n);
void writeData(byte* memory, short n);

#endif