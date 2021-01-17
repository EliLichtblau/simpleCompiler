#ifndef GEN_MIPS_h
#define GEN_MIPS_H

#include <stdio.h>

#define N_REGS 16


/*
 * Function declarations for generating assembly.
 * Generates MIPS assembly.
*/

extern int REGISTERS[N_REGS];
FILE *outfile;



// r1 = r1+r2
int add_registers(int r1, int r2);



// r1 = r1 -r2
int subtract_registers(int r1, int r2);


// r1 = r1 // r2 (I think mips defaults to integer divide)
int divide_registers(int r1, int r2);


// r1 *= r2
int multiply_registers(int r1, int r2);


int load_register(int value);
#endif