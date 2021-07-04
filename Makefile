SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := $(PWD)

EXE := $(BIN_DIR)/fansi
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -std=c89 -pedantic -Wall -ansi
CFLAGS   := -g # debugging symbols. TODO: turn off for prod build :P
LDFLAGS  :=
LDLIBS   :=

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
		$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
		mkdir -p $@

clean:
		@$(RM) -rv $(OBJ_DIR)
		@$(RM) $(BIN_DIR)/fansi

-include $(OBJ:.o=.d)
