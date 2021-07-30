#include "datatype.h"
#include <pthread.h>

#ifndef _MUTEX_H_
#define _MUTEX_H_

pthread_mutex_t io_metux;
bool lockAddress(unsigned long addr);
bool unlockAddress(unsigned long addr);

#endif