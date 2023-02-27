#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "tasc.h"

static char *read_file(const char *file_name); // Allocates a buffer in the heap for the string
static void write_file(const char *file_name, const char *src);

static uint32_t get_extension_index(const char *file_name);

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "error: no input files\n");
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		const char *file_name = argv[i];
		char *src = read_file(file_name);

		tasc_compile(file_name, src); // Frees src
	}

	return 0;
}

static char *read_file(const char *file_name)
{
	FILE *file = fopen(file_name, "r");
	if (file == NULL) {
		fprintf(stderr, "error: %s: cannot open file\n", file_name);
		exit(EXIT_FAILURE);
	}

	uint32_t extension_index = get_extension_index(file_name);
	if (strcmp(file_name + extension_index, ".tas") != 0) {
		fprintf(stderr, "error: %s: unrecognised file format\n", file_name);
		exit(EXIT_FAILURE);
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = malloc(file_size + 1);
	fread(buffer, sizeof(char), file_size, file);

	fclose(file);

	return buffer;
}

static void write_file(const char *file_name, const char *src)
{
	FILE *file = fopen(file_name, "w+");
	fwrite(src, sizeof(char), strlen(src), file);

	fclose(file);
}

static uint32_t get_extension_index(const char *file_name)
{
	uint32_t i;
	for (i = strlen(file_name) - 1; i != 0 && file_name[i] != '.'; --i);
	return i;
}
