#ifndef PARSER_H
#define PARSER_H

#include "symbol_table.h"

typedef struct node {
	struct node *left;
	struct node *right;
} Node;

Node *parser_parse(SymbolTable *table, const char *file_name, const char *src);


Node *ast_create(void);
void ast_destroy(Node *ast);

#endif // PARSER_H
