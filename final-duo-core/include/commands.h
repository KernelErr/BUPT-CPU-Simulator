#include "datatype.h"

#ifndef _COMMANDS_H_
#define _COMPANDS_H_

void mov(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void add(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void sub(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void mul(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void div(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void land(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void lor(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void lnot(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void cmp(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void jmp(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void in(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void out(int core_id, CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void lock(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void unlock(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void slp(CPU_Register_Typedef* registers, byte* memory, int dst, int data);

#endif