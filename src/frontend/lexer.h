#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>

#include "frontend/symbol_table.h"

typedef enum {
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,
	TOKEN_LEFT_BRACKET,
	TOKEN_RIGHT_BRACKET,
	TOKEN_LEFT_BRACE,
	TOKEN_RIGHT_BRACE,
	TOKEN_COMMA,
	TOKEN_SEMICOLON,
	TOKEN_BANG,
	TOKEN_EQUAL,
	TOKEN_NOT_EQUAL,
	TOKEN_LESS_THAN,
	TOKEN_GREATER_THAN,
	TOKEN_LESS_EQUAL_THAN,
	TOKEN_GREATER_EQUAL_THAN,
	TOKEN_AND_AND,
	TOKEN_AND_EQUALS,
	TOKEN_OR_OR,
	TOKEN_OR_EQUALS,
	TOKEN_ASSIGN,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_INCREMENT,
	TOKEN_DECREMENT,
	TOKEN_ASTERISK,
	TOKEN_DIVIDE,
	TOKEN_MODULO,
	TOKEN_DIVIDE_EQUALS,
	TOKEN_TIMES_EQUALS,
	TOKEN_PLUS_EQUALS,
	TOKEN_MINUS_EQUALS,
	TOKEN_MODULO_EQUALS,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_XOR,
	TOKEN_NOT,
	TOKEN_BITSHIFT_LEFT,
	TOKEN_BITSHIFT_RIGHT,
	TOKEN_BITSHIFT_LEFT_EQUALS,
	TOKEN_BITSHIFT_RIGHT_EQUALS,
	TOKEN_VOID,
	TOKEN_BOOL,
	TOKEN_TRUE,
	TOKEN_FALSE,
	TOKEN_CHAR,
	TOKEN_UCHAR,
	TOKEN_SHORT,
	TOKEN_USHORT,
	TOKEN_INT,
	TOKEN_UINT,
	TOKEN_LONG,
	TOKEN_ULONG,
	TOKEN_FLOAT32,
	TOKEN_FLOAT64,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_WHILE,
	TOKEN_FOR,
	TOKEN_CONTINUE,
	TOKEN_BREAK,
	TOKEN_RETURN,
	TOKEN_INT_LITERAL,
	TOKEN_FLOAT_LITERAL,
	TOKEN_CHARACTER_LITERAL,
	TOKEN_STRING_LITERAL,
	TOKEN_IDENTIFIER,
	TOKEN_EOF
} TokenType;

typedef struct lexer Lexer;

typedef struct {
	TokenType type;
	Symbol *value; // If the token is an identifier, it will point to the symbol table entry for that identifier
	uint64_t line, column;
} Token;

Lexer *lexer_create(SymbolTable *table, const char *file_name, const char *src);
void lexer_destroy(Lexer *lexer);

Token *lexer_next_token(Lexer *lexer);

#endif // lexer_h