/*
 * @Author: LI Rui
 * @Date: 2021-06-08 08:19:49
 * @LastEditTime: 2021-06-11 08:27:35
 * @LastEditors: LI Rui
 * @Description: IO模块
 * @FilePath: /final-duo-core/src/io.c
 * 
 */
#include <stdio.h>

short getUserInput() {
    short t = 0;
    printf("in:\n");
    scanf("%hd", &t);
    return t;
}

int printNum(int core_id, int n) {
    printf("id = %d    out: %d\n", core_id + 1, n);
}