CC := clang
CFLAGS := -Wall -Wextra -Iinclude
LDFLAGS := -lncurses -lpthread

SRC_DIR := src
OBJ_DIR := bin
BIN_DIR := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET := $(BIN_DIR)/blockbreaker

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/*.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean concat

concat_less:
	@cat $$(find . -name '*.c' -or -name '*.h') > combined_source.txt

concat:
	@cat $$(find . -name '*.c' -or -name '*.h') | tr -d " \t\n" | sed '/^\s*\/\//d' > combined_source_no_whitespace.txt

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
