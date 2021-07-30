#include "datatype.h"
#include "dump.h"
#include "interpreter.h"
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

CPU_Register_Typedef registers;
byte* memory;

void loadCode(byte* memory);
void panic(char* reason);

void init() {
    registers.ir = 0;
    registers.flag = 0;
    registers.ip = 0;
    for (int i = 1; i <= 8; i++) {
        registers.ax[i] = 0;
    }
    byte* memory = (byte*) malloc(32768);
    if (memory == NULL)
        panic("Unable to malloc memory.");
    loadCode(memory);
    while (true) {
        byte* command_addr = memory + registers.ip;
        if (command_addr >= (memory + DATA_Start)) {
            panic("Segment fault.");
        }
        registers.ir = byteToShort(command_addr);
        int data = byteToSignedOct(command_addr + 2);
        bool res = interpret(&registers, memory, registers.ir, data);
        dumpCPU(registers);
        if (res == false) {
            printf("\n");
            dumpCode(memory);
            printf("\n");
            dumpData(memory);
            break;
        }
    }
}

void loadCode(byte* memory) {
    char c;
    FILE* fp = NULL;
    int tmp = 0;
    int byte_counter = 0;
    byte* mem_addr = memory + CODE_Start;
    fp = fopen("dict.dic", "r");
    c = fgetc(fp);
    while (c != EOF && mem_addr <= (memory + DATA_Start - 1)) {
        if (byte_counter == 8) {
            *mem_addr = tmp;
            mem_addr++;
            byte_counter = 0;
            tmp = 0;
        }
        if (c == '0' || c == '1') {
            tmp <<= 1;
            tmp += (c - '0');
            byte_counter++;
        }
        c = fgetc(fp);
    }
}

void panic(char* reason) {
    printf("Kernel Panic at %d, reason: %s\n", registers.ip, reason);
    dumpCPU(registers);
    exit(-1);
}