/*
 * @Author: LI Rui
 * @Date: 2021-06-08 08:19:49
 * @LastEditTime: 2021-06-11 08:27:56
 * @LastEditors: LI Rui
 * @Description: 指令模块
 * @FilePath: /final-duo-core/src/commands.c
 * 
 */
#include "datatype.h"
#include "misc.h"
#include "io.h"
#include "mutex.h"
#include <unistd.h>
#include <pthread.h>

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

void div(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
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
