#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frontend/symbol_table.h"

typedef struct symbol_table {
	Symbol *hash_table;
	size_t hash_table_size;
	uint32_t entry_count;
} SymbolTable;

SymbolTable *st_create(size_t initial_size)
{
	SymbolTable *table = malloc(sizeof(SymbolTable));

	table->hash_table_size = initial_size;
	table->hash_table = calloc(initial_size, sizeof(Symbol));
	table->entry_count = 0;

	return table;
}

static unsigned int hash(const char *id, size_t table_size);
// static void double_table_size(SymbolTable *table);

void st_destroy(SymbolTable *table)
{
	for (int i = 0; i < table->hash_table_size; ++i) {
		Symbol *current_slot = table->hash_table + i;

		free(current_slot->id);

		Symbol *temp = current_slot->next;
		if (temp == NULL)
			continue;

		Symbol *temp2;
		while (1) {
			free(temp->id);
			temp2 = temp;

			if (temp->next == NULL) {
				free(temp);
				break;
			}
			else {
				temp = temp->next;
				free(temp2);
			}
		}
	}

	free(table->hash_table);
	free(table);
}

Symbol *st_get_symbol(SymbolTable *table, const char *value)
{
	Symbol *temp = table->hash_table + hash(value, table->hash_table_size);
	if (temp == NULL)
		return NULL;

	while (1) {
		if (temp->id == NULL)
			return NULL;
		else if (strcmp(temp->id, value) == 0)
			return temp;

		if (temp->next == NULL)
			return NULL;
		else
			temp = temp->next;
	}
}

Symbol *st_add_symbol(SymbolTable *table, char *value)
{
	// if (table->entry_count == table->hash_table_size)
	// 	double_table_size(table);

	++table->entry_count;
	size_t value_len = strlen(value);

	char *id = calloc(value_len + 1, sizeof(char));
	strcpy(id, value);

	unsigned int slot = hash(value, table->hash_table_size);
	Symbol *current = table->hash_table + slot;

	if (current->id == NULL) {
		current->id = id;
		current->id_length = value_len;

		return current;
	}
	else {
		Symbol *temp = current;

		while (temp->next != NULL)
			temp = temp->next;
		temp->next = calloc(1, sizeof(Symbol));
		temp = temp->next;

		temp->id = id;
		temp->id_length = value_len;

		return temp;
	}
}

void st_remove_symbol(SymbolTable *table, const char *value)
{
	if (table->hash_table_size == 0)
		return;

	--table->entry_count;

	unsigned int slot = hash(value, table->hash_table_size);

	if (table->hash_table[slot].id == NULL)
		return;

	Symbol *temp = table->hash_table + slot;
	while (strcmp(temp->id, value) != 0)
		temp = temp->next;

	free(temp->id);

	if (temp->next == NULL)
		memset(temp, 0, sizeof(Symbol));
	else
		memcpy(temp, temp->next, sizeof(Symbol));
}

void sb_print(SymbolTable *table)
{
	for (int i = 0; i < table->hash_table_size; ++i) {
		printf("entry %d: ", i + 1);

		Symbol *temp = table->hash_table + i;
		while (1) {
			if (temp->id != NULL)
				printf("%s", temp->id);
			else {
				printf("[empty]");
				break;
			}

			if (temp->next == NULL)
				break;

			temp = temp->next;

			printf(" | ");
		}

		putchar('\n');
	}
}

unsigned int hash(const char *id, size_t table_size)
{
	unsigned int length = strlen(id);
	unsigned int value = 0;

	for (int i = 0; i < length; ++i) {
		value = value * 37 + id[i];
	}
	value = value % table_size;

	return value;
}

// static void double_table_size(SymbolTable *table)
// {
// 	Symbol *old_table = table->hash_table;
// 	size_t old_table_size = table->hash_table_size;

// 	table->hash_table = calloc((table->hash_table_size *= 2), sizeof(Symbol));

// 	for (int i = 0; i < old_table_size; ++i)
// 		table->hash_table[hash(old_table[i].id, table->hash_table_size)] = old_table[i];

// 	free(old_table);
// }
