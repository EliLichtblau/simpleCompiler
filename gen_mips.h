
/*
 * Function declarations for generating assembly.
 * Generates MIPS assembly.
*/


// r1 = r1+r2
int reg_add(int r1, int r2);



// r1 = r1 -r2
int reg_subtract(int r1, int r2);


// r1 = r1 // r2 (I think mips defaults to integer divide)
int reg_divide(int r1, int r2);


// r1 *= r2
int reg_multiply(int r1, int r2);