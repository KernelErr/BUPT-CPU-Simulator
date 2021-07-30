#include "datatype.h"
#include "misc.h"
#include "io.h"

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
    int first_reg = getFirstReg(dst);
    registers->ax[first_reg] = getUserInput();
    registers->ip += 4;
}

void out(CPU_Register_Typedef* registers, byte* memory, int dst, int data) {
    int first_reg = getFirstReg(dst);
    printNum(registers->ax[first_reg]);
    registers->ip += 4;
}