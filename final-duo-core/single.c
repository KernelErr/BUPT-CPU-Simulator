/*
 * @Author: LI Rui
 * @Date: 2021-06-08 08:19:49
 * @LastEditTime: 2021-06-14 21:35:50
 * @LastEditors: LI Rui
 * @Description: 
 * @FilePath: /final-duo-core/single.c
 * 
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t address_mutexes[16384] = {PTHREAD_MUTEX_INITIALIZER};

#ifndef _DATATYPE_H_
#define _DATATYPE_H_

typedef unsigned char byte;

typedef short reg;

typedef struct {
    reg ip, ir;
    reg ax[9];
    short flag;
} CPU_Register_Typedef;

typedef struct {
    int core_id;
    byte* memory;
} KERNEL_ARGS;

#define CODE_Start 0
#define DATA_Start 16384

#define true 1
#define false 0
#define bool int

#define NTHREADS 2

#endif

#ifndef _MUTEX_H_
#define _MUTEX_H_

pthread_mutex_t io_metux;
bool lockAddress(unsigned long addr);
bool unlockAddress(unsigned long addr);

#endif

#ifndef _MISC_H_
#define _MISC_H_

int byteToOct(byte* memory);
short byteToShort(byte* memory);
int byteToSignedOct(byte* memory);
int getFirstReg(int n);
int getSecondReg(int n);
void writeData(byte* memory, short n);

#endif

#ifndef _KERNEL_H_
#define _KERNEL_H_

void* init(void* args);

#endif

#ifndef _IO_H_
#define _IO_H_

short getUserInput();
int printNum(int core_id, int n);

#endif

#ifndef _INTERPRETER_H_
#define _INTERPRETER_H

bool interpret(int core_id, CPU_Register_Typedef* registers, byte* memory, int command, int data);

#endif

#ifndef _DUMP_H_
#define _DUMP_H_

void dumpCPU(int core_id, CPU_Register_Typedef registers);
void dumpCode(byte* memory);
void dumpData(byte* memory);

#endif

#ifndef _COMMANDS_H_
#define _COMPANDS_H_

void mov(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void add(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void sub(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void mul(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
void divi(CPU_Register_Typedef* registers, byte* memory, int dst, int data);
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

void mov(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        registers->ax[first_reg] = data;
    } else {
        if (second_reg >= 5) {
            registers->ax[first_reg] = byteToShort(memory + registers->ax[second_reg]);
        } else {
            writeData(memory + registers->ax[first_reg], registers->ax[second_reg]);
        }
    }
    registers->ip += 4;
}

void add(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        registers->ax[first_reg] += data;
    } else {
        registers->ax[first_reg] += byteToShort(memory + registers->ax[second_reg]);
    }
    registers->ip += 4;
}

void sub(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        registers->ax[first_reg] -= data;
    } else {
        registers->ax[first_reg] -= byteToShort(memory + registers->ax[second_reg]);
    }
    registers->ip += 4;
}

void mul(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        registers->ax[first_reg] *= data;
    } else {
        registers->ax[first_reg] *= byteToShort(memory + registers->ax[second_reg]);
    }
    registers->ip += 4;
}

void divi(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        registers->ax[first_reg] /= data;
    } else {
        registers->ax[first_reg] /= byteToShort(memory + registers->ax[second_reg]);
    }
    registers->ip += 4;
}

void land(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        registers->ax[first_reg] = registers->ax[first_reg] && data;
    } else {
        registers->ax[first_reg] = registers->ax[first_reg] && byteToShort(memory + registers->ax[second_reg]);
    }
    registers->ip += 4;
}

void lor(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        registers->ax[first_reg] = registers->ax[first_reg] || data;
    } else {
        registers->ax[first_reg] = registers->ax[first_reg] || byteToShort(memory + registers->ax[second_reg]);
    }
    registers->ip += 4;
}

void lnot(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        registers->ax[first_reg] = !registers->ax[first_reg];
    } else {
        writeData(memory + registers->ax[second_reg], !byteToShort(memory + registers->ax[second_reg]));
    }
    registers->ip += 4;
}

void cmp(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    int second_reg = getSecondReg(dst);
    if (second_reg == 0) {
        if (registers->ax[first_reg] == data) {
            registers->flag = 0;
        } else if (registers->ax[first_reg] > data) {
            registers->flag = 1;
        } else {
            registers->flag = -1;
        }
    } else {
        int t = byteToShort(memory + registers->ax[second_reg]);
        if (registers->ax[first_reg] == t) {
            registers->flag = 0;
        } else if (registers->ax[first_reg] > t) {
            registers->flag = 1;
        } else {
            registers->flag = -1;
        }
    }
    registers->ip += 4;
}

void jmp(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int bit = getSecondReg(dst);
    if (bit == 0) {
        registers->ip += data;
        return;
    }
    if (bit == 1) {
        if (registers->flag == 0) {
            registers->ip += data;
        } else {
            registers->ip += 4;
        }
        return;
    }
    if (bit == 2) {
        if (registers->flag == 1) {
            registers->ip += data;
        } else {
            registers->ip += 4;
        }
        return;
    }
    if (bit == 3) {
        if (registers->flag == -1) {
            registers->ip += data;
        } else {
            registers->ip += 4;
        }
        return;
    }
}

void in(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    pthread_mutex_lock(&io_metux);
    int first_reg = getFirstReg(dst);
    registers->ax[first_reg] = getUserInput();
    registers->ip += 4;
    pthread_mutex_unlock(&io_metux);
}

void out(int core_id, CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    pthread_mutex_lock(&io_metux);
    int first_reg = getFirstReg(dst);
    printNum(core_id, registers->ax[first_reg]);
    registers->ip += 4;
    pthread_mutex_unlock(&io_metux);
}

void lock(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    lockAddress(data);
    registers->ip += 4;
}

void unlock(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    unlockAddress(data);
    registers->ip += 4;
}

void slp(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    usleep(data * 1000);
    registers->ip += 4;
}

void dumpCPU(int core_id, CPU_Register_Typedef registers) {
    pthread_mutex_lock(&io_metux);
    printf("id = %d\n", core_id);
    printf("ip = %d\n", registers.ip);
    printf("flag = %d\n", registers.flag);
    printf("ir = %d\n", registers.ir);
    printf("ax1 = %d ax2 = %d ax3 = %d ax4 = %d\n", registers.ax[1], registers.ax[2], registers.ax[3], registers.ax[4]);
    printf("ax5 = %d ax6 = %d ax7 = %d ax8 = %d\n", registers.ax[5], registers.ax[6], registers.ax[7], registers.ax[8]);
    pthread_mutex_unlock(&io_metux);
}

void dumpCode(byte* memory) {
    byte* mem_addr = memory + CODE_Start;
    byte* p = mem_addr;
    printf("codeSegment :\n");
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d", byteToOct(p));
            if (j < 7)
                printf(" ");
            p += 4;
        }
        printf("\n");
    }
}

void dumpData(byte* memory) {
    byte* mem_addr = memory + DATA_Start;
    byte* p = mem_addr;
    printf("dataSegment :\n");
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%d", byteToShort(p));
            if (j < 15)
                printf(" ");
            p += 2;
        }
        printf("\n");
    }
}

bool interpret(int core_id, CPU_Register_Typedef* registers, byte* memory, int command, int data) {
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
            divi(registers, memory, dst, data);
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
            out(core_id, registers, memory, dst, data);
            break;
        case 13:
            lock(registers, memory, dst, data);
            break;
        case 14:
            unlock(registers, memory, dst, data);
            break;
        case 15:
            slp(registers, memory, dst, data);
            break;
    }
    return true;
}

short getUserInput() {
    short t = 0;
    printf("in:\n");
    scanf("%hd", &t);
    return t;
}

int printNum(int core_id, int n) {
    printf("id = %d    out: %d\n", core_id + 1, n);
}

void loadCode(int core_id, byte* memory);

/**
 * @description: 内核初始化及调度
 * @param  {KERNEL_ARGS} args Args contains the core id and memory start pointer
 */
void* init(void* args) {
    int core_id = ((KERNEL_ARGS*)args)->core_id;
    byte* memory = ((KERNEL_ARGS*)args)->memory;
    CPU_Register_Typedef registers;
    registers.ir = 0;
    registers.flag = 0;
    registers.ip = 256 * core_id;
    for (int i = 1; i <= 8; i++) {
        registers.ax[i] = 0;
    }
    loadCode(core_id, memory);
    while (true) {
        byte* command_addr = memory + registers.ip;
        registers.ir = byteToShort(command_addr);
        int data = byteToSignedOct(command_addr + 2);
        bool res = interpret(core_id, &registers, memory, registers.ir, data);
        dumpCPU(core_id + 1, registers);
        if (res == false) {
            break;
        }
    }
}

/**
 * @description: 载入代码到内存
 * @param {int} core_id
 * @param {byte*} memory
 */
void loadCode(int core_id, byte* memory) {
    char c;
    FILE* fp = NULL;
    int tmp = 0;
    int byte_counter = 0;
    byte* mem_addr = memory + CODE_Start + 256 * core_id;
    if (core_id == 0) {
        fp = fopen("dict1.dic", "r");
    } else {
        fp = fopen("dict2.dic", "r");
    }
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

bool lockAddress(unsigned long addr) {
    if (addr < 16384 || addr >= 32768) {
        return false;
    }
    if (!pthread_mutex_lock(&address_mutexes[addr - 16384])) {
        return true;
    } else {
        return false;
    }
}

/**
 * @description: 解锁指定地址
 * @param {unsigned long} addr Target address
 * @return {bool} Shows if unlocked the mutex successfully
 */
bool unlockAddress(unsigned long addr) {
    if (addr < 16384 || addr >= 32768) {
        return false;
    }
    if (!pthread_mutex_unlock(&address_mutexes[addr - 16384])) {
        return true;
    } else {
        return false;
    }
}

int main() {
    pthread_t thread_id[NTHREADS];
    KERNEL_ARGS args[NTHREADS];
    byte* memory = (byte*) malloc(32768);

    writeData(memory + 16384, 100);

    for (int i = 0; i < NTHREADS; i++) {
        args[i].core_id = i;
        args[i].memory = memory;
        pthread_create(&thread_id[i], NULL, init, &args[i]);
    }

    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    printf("\n");
    dumpCode(memory);
    printf("\n");
    dumpData(memory);

    return 0;
}
