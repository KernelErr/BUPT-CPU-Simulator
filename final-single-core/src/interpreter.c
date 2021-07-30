#include "datatype.h"
#include "misc.h"
#include "commands.h"
#include <stdio.h>

bool interpret(CPU_Register_Typedef* registers, byte* memory, int command, int data) {
    int cmd = command >> 8;
    int dst = command & 255;
    switch (cmd) {
        case 0:
            registers->ip += 4;
            return false;
        case 1:
            mov(registers, memory, dst, data);
            break;
        case 2:
            add(registers, memory, dst, data);
            break;
        case 3:
            sub(registers, memory, dst, data);
            break;
        case 4:
            mul(registers, memory, dst, data);
            break;
        case 5:
            div(registers, memory, dst, data);
            break;
        case 6:
            land(registers, memory, dst, data);
            break;
        case 7:
            lor(registers, memory, dst, data);
            break;
        case 8:
            lnot(registers, memory, dst, data);
            break;
        case 9:
            cmp(registers, memory, dst, data);
            break;
        case 10:
            jmp(registers, memory, dst, data);
            break;
        case 11:
            in(registers, memory, dst, data);
            break;
        case 12:
            out(registers, memory, dst, data);
            break;
    }
    return true;
}