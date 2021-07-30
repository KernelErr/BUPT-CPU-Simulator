/*
 * @Author: LI Rui
 * @Date: 2021-06-08 08:19:49
 * @LastEditTime: 2021-06-11 08:28:07
 * @LastEditors: LI Rui
 * @Description: 主模块
 * @FilePath: /final-duo-core/main.c
 * 
 */
#include "kernel.h"
#include "datatype.h"
#include "dump.h"
#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
