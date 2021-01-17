CC = gcc 



all: parse_expression.x clean_object


parse_expression.x: parse_expression.h parse_expression.c lexer.o
	$(CC) parse_expression.c lexer.o -o parse_expression.x
	
	
parse_expression.o: parse_expression.h parse_expression.c lexer.o
	$(CC) -c parse_expression.c

lexer.o: lexing/lexer.h lexing/lexer.c
	$(CC) -c lexing/lexer.c

parse_expression.h:
	touch parse_expression.h


lexer.h: lexing/lexer.h
	touch ../lexer.h


clean_object:
	rm -rf *.o
