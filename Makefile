NC     = \033[0m
BLUE   = \033[1;34m
CYAN   = \033[1;36m
GREEN  = \033[1;32m
YELLOW = \033[1;33m

CC = clang
LD = clang

CFLAGS =  -std=c11 -Wall -pedantic -Isrc -O0 -g -gdwarf-4

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard, $d/, $2) $(filter $(subst *, %, $2), $d))

OBJ_DIR = build/obj
SRC     = $(call rwildcard, src, *.c)
OBJ     = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

EXE = build/tasc

.PHONY: all clean

all: $(OBJ)
	@ echo -e "$(GREEN)LINKING EXECUTABLE$(NC) $(EXE)"
	@ $(LD) $(OBJ) -o $(EXE) $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.c
	@ mkdir -p $(@D)
	@ echo -e "$(GREEN)COMPILING OBJECT$(NC) $@"
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ echo -e "$(YELLOW)CLEANING PROJECT$(NC)"
	@ rm -rf build
