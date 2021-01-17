#include "lexing/lexer.h"

#include "parse_expression.h"

#include <stdlib.h>
#include <stdio.h>


static Expression *new_expression();
static Expression *parse_add(TokenList *token_list);
static Expression *parse_mult(TokenList *token_list);
static Expression *parse_primary(TokenList *token_list);
static void printExpression(Expression *expr);

static Expression *new_expression() {
	Expression *expression = malloc(sizeof(Expression));
	expression->left = NULL;
	expression->right = NULL;
	expression->operator = 0;
	expression->value = 0;
}

//static void push_expression(Expression *expression, )

Expression *copy_expression(Expression *expr) {
	if (expr == NULL)
		return NULL;

	Expression *copy = new_expression();
	copy->operator = expr->operator;
	copy->value = expr->value;
	copy->left = copy_expression(expr->left);
	copy->right = copy_expression(expr->right);

	return copy;

} 





Expression *parse_expression(TokenList *token_list) {
	return parse_add(token_list);
}


static Expression *parse_add(TokenList *token_list) {
	Expression *expr;
	Expression *after_parse_mult = parse_mult(token_list);

	LexToken *head = peek(token_list);

	if (head == NULL)
		return after_parse_mult;

	switch (head->token_type) {
		case TOK_PLUS:
			expr = new_expression();
			pop(token_list);
			expr->left = copy_expression(after_parse_mult);
			expr->operator = PLUS;
			expr->right = parse_add(token_list);
			return expr;

		case TOK_SUB:
			expr = new_expression();
			pop(token_list);
			expr->left = copy_expression(after_parse_mult);
			expr->operator = SUB;
			expr->right = parse_add(token_list);
			return expr;

	} 

	return after_parse_mult;

}


static Expression *parse_mult(TokenList *token_list) {
	Expression *expr;
	Expression *after_parse_primary = parse_primary(token_list);

	LexToken *head = peek(token_list);

	if (head == NULL)
		return after_parse_primary;

	switch (head->token_type) {
		case TOK_MULT:
			expr = new_expression();
			pop(token_list);
			expr->left = copy_expression(after_parse_primary);
			expr->operator = MULT;
			expr->right = parse_mult(token_list);
			return expr;

		case TOK_DIV:
			expr = new_expression();
			pop(token_list);
			expr->left = copy_expression(after_parse_primary);
			expr->operator = DIV;
			expr->right = parse_mult(token_list);
			return expr;

	} 

	return after_parse_primary;

}



static Expression *parse_primary(TokenList *token_list) {
	LexToken *head = peek(token_list);
	Expression *expr;

	if (token_list->head == NULL) {
		printf("Missing Value!\n");
		exit(-1);
	}

	switch (head->token_type) {
		case TOK_INT:
			expr = new_expression();
			expr->operator = INT;
			expr->value = head->value;
			pop(token_list);
			return expr;
		case TOK_LPAREN:
			//expr = new_expression();
			pop(token_list);
			expr = parse_add(token_list);
			//print_lex_tokens(token_list);
			LexToken *head = peek(token_list);
			if (head == NULL || head->token_type != TOK_RPAREN) {
				printf("Missing matching ')'\n");
				exit(1);
			}
			pop(token_list);
			return expr;

	}


}


static void print_expresson(Expression *expr) {
	if (expr == NULL)
		return;

	print_expresson(expr->left);
	printf("%d\n", expr->value);
	print_expresson(expr->right);
}



static int intepret(Expression *expr) {
	int left, right;
	if (expr == NULL)
		return 0;


	left = intepret(expr->left);
	right = intepret(expr->right);
	switch (expr->operator) {
		case PLUS:
			return left+right;


		case SUB:
			return left-right;

		case MULT:
			return left*right;

		case DIV:
			return left/right;

		case INT:
			return expr->value;

		default:
			return 0;
	}




}




/*
int main() {

	char *str = "(7+3*6)*6";
	TokenList *list = tokenize(&str);
	//print_lex_tokens(list);
	Expression *expr = parse_expression(list);
	print_expresson(expr);

	printf("%d\n", intepret(expr));

	return 0;
}
*/