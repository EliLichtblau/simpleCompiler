#include "gen_mips.h"
#include <stdlib.h>
#include <stido.h>

FILE *outfile = NULL;




int add_registers(int r1, int r2) {
	fprintf(outfile, "add $r%d $r%d\n", r1, r2);
	return r1;
}

int subtract_registers(int r1, int r2) {
	fprintf(outfile, "sub $r%d $r%d\n", r1, r2);
	return r1;
}

int multiply_registers(int r1, int r2) {
	fprintf(outfile, "mul $r%d $r%d\n", r1, r2);
	return r1;
}

int divide_registers(int r1, int r2) {
	fprintf(outfile, "div $r%d $r%d\n", r1, r2);
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

	fprintf(outfile, "li $r%d %d\n", reg, value);
	return reg;
}


void free_register(int reg) {
	REGISTERS[reg] = 1;
}



int alloc_register() {
	int i;
	for (i = 0; i < N_REGS; i++) {
		if (REGISTERS[i] == 1) {
			REGISTERS[i] = 0;
			return i;
		}
	}

	return -1;
}