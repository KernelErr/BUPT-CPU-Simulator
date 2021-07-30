#include "datatype.h"
#include "misc.h"
#include <stdio.h>

void dumpCPU(CPU_Register_Typedef registers) {
    printf("ip = %d\n", registers.ip);
    printf("flag = %d\n", registers.flag);
    printf("ir = %d\n", registers.ir);
    printf("ax1 = %d ax2 = %d ax3 = %d ax4 = %d\n", registers.ax[1], registers.ax[2], registers.ax[3], registers.ax[4]);
    printf("ax5 = %d ax6 = %d ax7 = %d ax8 = %d\n", registers.ax[5], registers.ax[6], registers.ax[7], registers.ax[8]);
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