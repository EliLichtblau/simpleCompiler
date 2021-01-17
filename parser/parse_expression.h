#ifndef PARSE_EXPRESSION_H
#define PARSE_EXPRESSION_H

#include "lexing/lexer.h"
#define PLUS 0
#define MULT 1
#define DIV 2
#define SUB 3
#define INT 4






typedef struct _expr {
	int operator;
	int value;
	struct _expr *left;
	struct _expr *right;

} Expression;



Expression *copy_expression(Expression *);


Expression *parse_expression(TokenList *);

#endif