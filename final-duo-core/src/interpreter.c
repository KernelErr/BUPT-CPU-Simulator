/*
 * @Author: LI Rui
 * @Date: 2021-06-08 08:19:49
 * @LastEditTime: 2021-06-11 08:34:24
 * @LastEditors: LI Rui
 * @Description: 解释器模块
 * @FilePath: /final-duo-core/src/interpreter.c
 * 
 */
#include "datatype.h"
#include "misc.h"
#include "commands.h"
#include <stdio.h>

/**
 * @description: 指令解释函数
 * @param {int} core_id
 * @param {int} command
 * @param {int} data
 * @return {*}
 */
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