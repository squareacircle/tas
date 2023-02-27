#include <pcre2posix.h>

#include <stdbool.h>

#include "tasc.h"
#include "frontend/lexer.h"

#define IDENTIFIER_LENGTH 128

typedef struct lexer {
	SymbolTable *table;

	const char *file;
	const char *src;
	size_t src_length;
	uint64_t index;

	uint64_t line, column;

	char lexeme[IDENTIFIER_LENGTH + 1]; // + 1 for the null character
	regex_t identifier_reg, valid_int_reg, invalid_int_reg, valid_float_reg, invalid_float_reg;

	Token *token;
} Lexer;

static void regex_compile(regex_t *dest, const char *src, int cflags);
static bool regex_match(const char *src, regex_t *regex);

static inline void set_current_token(Lexer *lexer, TokenType type);

static void regex_compile(regex_t *dest, const char *src, int cflags)
{
	if (pcre2_regcomp(dest, src, cflags) != 0)
		tasc_internal_error("regex complilation failed\n");
}

static bool regex_match(const char *src, regex_t *regex)
{
	if (pcre2_regexec(regex, src, 0, NULL, 0) == 0)
		return true;
	else
		return false;
}

static inline void set_current_token(Lexer *lexer, TokenType type)
{
	lexer->token->type = type;

	Symbol *value = NULL;
	if (type == TOKEN_IDENTIFIER || type == TOKEN_INT_LITERAL || type == TOKEN_FLOAT_LITERAL ||
	    type == TOKEN_CHARACTER_LITERAL || type == TOKEN_STRING_LITERAL) {
		if ((value = st_get_symbol(lexer->table, lexer->lexeme)) == NULL)
			value = st_add_symbol(lexer->table, lexer->lexeme);
	}
	lexer->token->value = value;

	lexer->token->line = lexer->line;
	lexer->token->column = lexer->column;
}