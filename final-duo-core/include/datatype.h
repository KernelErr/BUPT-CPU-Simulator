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