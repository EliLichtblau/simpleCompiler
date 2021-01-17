#ifndef LEXER_H
#define LEXER_H

#define TOK_LPAREN 0
#define TOK_RPAREN 1
#define TOK_INT 2
#define TOK_PLUS 3
#define TOK_MULT 4
#define TOK_DIV 5
#define TOK_SUB 6

/* convert passed token to string */
#define INT_TO_TOKEN_NAME \
	GEN_TOKEN(TOK_LPAREN)  \
	GEN_TOKEN(TOK_RPAREN)  \
	GEN_TOKEN(TOK_INT)  \
	GEN_TOKEN(TOK_PLUS)  \
	GEN_TOKEN(TOK_MULT)  \
	GEN_TOKEN(TOK_DIV)  \
	GEN_TOKEN(TOK_SUB)  \


#define GEN_TOKEN(STRING) #STRING,






typedef struct _lex_token{
	int token_type;

	int value; //if int


	struct _lex_token *next; //store in linked list

} LexToken;



typedef struct {
	LexToken *head;
	LexToken *tail;

} TokenList;


LexToken *match_token(char **str);
TokenList *tokenize(char **str);
void print_lex_tokens(TokenList *);

LexToken *peek(TokenList *token_list);
void pop(TokenList *token_list);


#endif