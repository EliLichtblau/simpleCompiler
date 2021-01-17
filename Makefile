CC = gcc 



all: main.x clean_object




main.x: main.c gen_mips.o parse_expression.o lexer.o
	$(CC) main.c parse_expression.o  lexer.o gen_mips.o -o main.x


gen_mips.o: gen_mips.c gen_mips.h
	$(CC) -c gen_mips.c

parse_expression.x: parse_expression.h parse_expression.c lexer.o
	$(CC) parser/parse_expression.c lexer.o -o parse_expression.x
	
	
parse_expression.o: parse_expression.h parse_expression.c lexer.o
	$(CC) -c parser/parse_expression.c

lexer.o: lexer.h lexer.c
	$(CC) -c parser/lexing/lexer.c


parse_expression.c:
	touch parser/parse_expression.c

parse_expression.h:
	touch parser/parse_expression.h


lexer.c:
	touch parser/lexing/lexer.c

lexer.h: 
	touch parser/lexing/lexer.h


clean_object:
	rm -rf *.o
