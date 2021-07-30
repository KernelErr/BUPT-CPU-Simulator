/*
 * @Author: LI Rui
 * @Date: 2021-06-08 08:19:49
 * @LastEditTime: 2021-06-11 08:27:08
 * @LastEditors: LI Rui
 * @Description: 线程锁控制模块
 * @FilePath: /final-duo-core/src/mutex.c
 * 
 */
#include "datatype.h"
#include <pthread.h>

pthread_mutex_t address_mutexes[16384] = {PTHREAD_MUTEX_INITIALIZER};

/**
 * @description: 锁定指定地址
 * @param {unsigned long} addr Target address
 * @return {bool} Shows if locked the mutex successfully
 */
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