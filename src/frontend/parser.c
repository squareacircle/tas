#include <stdio.h>
#include <stdlib.h>

#include "frontend/lexer.h"
#include "frontend/parser.h"

typedef struct {
	SymbolTable *table;
	Node *ast;
	Lexer *lexer;
} Parser;

Node *parser_parse(SymbolTable *table, const char *file_name, const char *src)
{
	Parser *this = malloc(sizeof(Parser));
	this->ast = ast_create();
	this->lexer = lexer_create(table, file_name, src);



	Node *ast = this->ast;

	lexer_destroy(this->lexer);
	free(this);

	return ast;
}

Node *ast_create(void)
{
	Node *ast = malloc(sizeof(Node));

	return ast;
}

void ast_destroy(Node *ast)
{
	free(ast);
}

