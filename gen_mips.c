#include "gen_mips.h"
#include <stdlib.h>
#include <stdio.h>

static void free_register(int reg);
static int alloc_register();

int REGISTERS[] = {
	1,1,1,1,
	1,1,1,1,
	1,1,1,1,
	1,1,1,1
};


int add_registers(int r1, int r2) {
	fprintf(outfile, "add $t%d, $t%d, $t%d \n", r1, r2, r1);
	free_register(r2);
	return r1;
}

int subtract_registers(int r1, int r2) {
	fprintf(outfile, "sub $t%d, $t%d, $t%d \n", r1, r2, r1);
	free_register(r2);
	return r1;
}

int multiply_registers(int r1, int r2) {
	fprintf(outfile, "mul $t%d, $t%d, $t%d \n", r1, r2, r1);
	free_register(r2);
	return r1;
}

int divide_registers(int r1, int r2) {
	fprintf(outfile, "div $t%d, $t%d, $t%d \n", r1, r2, r1);
	free_register(r2);
	return r1;

}


int load_register(int value) {
	int reg;

	reg = alloc_register();

	//Just throws error on no more registers
	//I'll implement something eventually
	if (reg == -1) {
		printf("Out of registers... someone should implement graph coloring or something\n");
		exit(1);
	}

	fprintf(outfile, "li $t%d, %d\n", reg, value);
	return reg;
}


static void free_register(int reg) {
	REGISTERS[reg] = 1;
}



static int alloc_register() {
	int i;
	for (i = 0; i < N_REGS; i++) {
		if (REGISTERS[i] == 1) {
			REGISTERS[i] = 0;
			return i;
		}
	}

	return -1;
}

