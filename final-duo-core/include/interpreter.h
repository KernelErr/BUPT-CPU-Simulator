#ifndef _INTERPRETER_H_
#define _INTERPRETER_H

bool interpret(int core_id, CPU_Register_Typedef* registers, byte* memory, int command, int data);

#endif