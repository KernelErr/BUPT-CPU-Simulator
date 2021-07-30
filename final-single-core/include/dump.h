#include "datatype.h"

#ifndef _DUMP_H_
#define _DUMP_H_

void dumpCPU(CPU_Register_Typedef registers);
void dumpCode(byte* memory);
void dumpData(byte* memory);

#endif