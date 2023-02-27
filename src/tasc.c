#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>

#include "tasc.h"
#include "symbol_table.h"
#include "frontend/parser.h"

char *tasc_compile(const char *file_name, char *src)
{
	SymbolTable *table = st_create(256);

	Node *ast = parser_parse(table, file_name, src);

	free(src);
	ast_destroy(ast);
	st_destroy(table);

	return NULL;
}

void tasc_internal_error(const char *message, ...)
{
	fprintf(stderr, RED_BOLD "internal error: " RESET);

	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);

	fprintf(stderr, "aborting.\n");
	exit(EXIT_FAILURE);
}

void tasc_error(const char *file, uint64_t line, uint64_t column, const char *message, ...)
{
	fprintf(stderr, WHITE_BOLD "%s:%"PRIu64":%"PRIu64": " RESET RED_BOLD "error: " RESET, file, line, column);

	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);

	fprintf(stderr, "aborting\n");
	exit(EXIT_FAILURE);
}

void tasc_warning(const char *file, uint64_t line, uint64_t column, const char *message, ...)
{
	fprintf(stderr, WHITE_BOLD "%s:%"PRIu64":%"PRIu64": " RESET MAGENTA_BOLD "warning: " RESET, file, line, column);

	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);
}
