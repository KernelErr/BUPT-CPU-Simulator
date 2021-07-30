/*
 * @Author: LI Rui
 * @Date: 2021-06-08 08:19:49
 * @LastEditTime: 2021-06-11 08:27:16
 * @LastEditors: LI Rui
 * @Description: 内核调度模块
 * @FilePath: /final-duo-core/src/kernel.c
 * 
 */
#include "datatype.h"
#include "dump.h"
#include "interpreter.h"
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

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