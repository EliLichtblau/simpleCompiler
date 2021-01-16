#include "lexer.h"
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static LexToken *new_token();
static int regex_match(const char *reg_expr, char *string);

/* 
 * Given a regex expression and a string
 * Return 1 on match, 0 on no match.
*/
static int regex_match(const char *reg_expr, char *string) {
	regex_t regex;
	regmatch_t match[1];
	regcomp(&regex, reg_expr, REG_EXTENDED);
	int check_match = regexec(&regex, string, 1, match, 0);
	regfree(&regex);
	if (!check_match) 
		return match[0].rm_eo;
	return 0;
}



/* For Debugging, print token names*/
static const char *NUM_TO_TOKEN[] = {
    INT_TO_TOKEN_NAME
};





static LexToken *new_token() {
	LexToken *token = malloc(sizeof(LexToken));
	token->next = NULL;
	return token;
}


/*

15 + 7
+ 7

*/
LexToken *match_token(char **str) {
	LexToken *token = NULL;
	int length;
	char *tmp;
	if (strlen(*str) == 0) {
		return NULL;
	}


	if (length = regex_match("^(\\s)*(\\-)?(([0-9]+\\.?[0-9]*)|[0-9]*\\.[0-9]+)", *str)) {
		token = new_token();
		token->token_type = TOK_INT;
		tmp = malloc(length+1);
		strncpy(tmp, *str, length);
		token->value = atoi(tmp);
		(*str) += length;
		free(tmp);
	} else if (length = regex_match("^(\\s)*\\+", *str)) {
		token = new_token();
		token->token_type = TOK_PLUS;
		(*str) += length;
	} else if (length = regex_match("^(\\s)*\\-", *str)) {
		token = new_token();
		token->token_type = TOK_SUB;
		(*str) += length;
	} else if (length = regex_match("^(\\s)*\\*", *str)) {
		token = new_token();
		token->token_type = TOK_MULT;
		(*str) += length;
	} else if (length = regex_match("^(\\s)*/", *str)) {
		token = new_token();
		token->token_type = TOK_DIV;
		(*str) += length;
	} else if (length = regex_match("^(\\s)*\\(", *str)) {
		token = new_token();
		token->token_type = TOK_LPAREN;
		(*str) += length;
	} else if (length = regex_match("^(\\s)*\\)", *str)) {
		token = new_token();
		token->token_type = TOK_RPAREN;
		(*str) += length;
	}
	return token;

}	






LexToken *tokenize(char **str) {
	LexToken *head = NULL;
	LexToken *tail;
	LexToken *token;
	while ((token = match_token(str)) != NULL) {
		if (head == NULL) {
			head = token;
			tail = token;
		} else {
			tail->next = token;
			tail = token;
		}
		
	}

	return head;
}



void print_lex_tokens(LexToken *head) {
	while (head != NULL) {
		if (head ->token_type == TOK_INT) 
			printf("(%s; %d) ", NUM_TO_TOKEN[head->token_type], head->value);
		else
			printf("(%s) ", NUM_TO_TOKEN[head->token_type]);
		
		head = head->next;
	}
	printf("\n");
}



int main() {
	char *str = "(71+3)*4";
	//match_token(&str);
	print_lex_tokens(tokenize(&str));
	//int r = regex_match("^(\\s)*(\\-)?(([0-9]+\\.?[0-9]*)|[0-9]*\\.[0-9]+)",str);
	//printf("%d\n", r);
}


