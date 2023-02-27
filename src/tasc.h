#ifndef TASC_H
#define TASC_H

#include <stdint.h>

#define RESET        "\033[0m"
#define RED_BOLD     "\033[1;31m"
#define WHITE_BOLD   "\033[1;39m"
#define MAGENTA_BOLD "\033[1;35m"

char *tasc_compile(const char *file_name, char *src);

void tasc_internal_error(const char *message, ...);
void tasc_error(const char *file, uint64_t line, uint64_t column, const char *message, ...);
void tasc_warning(const char *file, uint64_t line, uint64_t column, const char *message, ...);

#endif // TASC_H
