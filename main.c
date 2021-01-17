#include "gen_mips.h"
#include "parser/parse_expression.h"


static void print_expresson(Expression *expr) {
	if (expr == NULL)
		return;

	print_expresson(expr->left);
	printf("%d\n", expr->value);
	print_expresson(expr->right);
}



static int generate_mips(Expression *expr) {
	if (expr == NULL)
		return 0;

	int left_reg = generate_mips(expr->left);
	int right_reg = generate_mips(expr->right);
	switch (expr->operator) {
		case PLUS: return add_registers(left_reg, right_reg);

		case MULT: return multiply_registers(left_reg, right_reg);

		case DIV: return divide_registers(left_reg, right_reg);

		case SUB: return subtract_registers(left_reg, right_reg);

		case INT: return load_register(expr->value);
	}


	return 0;
}





extern FILE *outfile;

int main() {
	char *str = "(7+3*6)*6";
	TokenList *list = tokenize(&str);
	//print_lex_tokens(list);
	Expression *expr = parse_expression(list);
	print_expresson(expr);


	outfile = fopen("out.asm", "w");
	fprintf(outfile, "main:\n");
	generate_mips(expr);
	fprintf(outfile, "li $v0, 10\nsyscall");
	fclose(outfile);

	//printf("%p\n", outfile);
	return 0;
}