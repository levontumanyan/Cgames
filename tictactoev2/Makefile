# Define the C compiler to use
CC := clang

# Define variables
SRC_DIR := src
OBJ_DIR := bin
BIN_DIR := bin

# Define any compile-time flags
CFLAGS := -g -Wall -Wextra -I/opt/homebrew/Cellar/allegro/5.2.9.1/include -Iinclude

# Define library paths in addition to /usr/lib
LDFLAGS = -L/opt/homebrew/Cellar/allegro/5.2.9.1/lib

# Define any libraries to link into executable:
LIBS = -lallegro -lallegro_main -lallegro_primitives

# Define the C source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET := $(BIN_DIR)/tictactoe

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/*.h | $(OBJ_DIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ_FILES) $(LIBS)

.PHONY: clean
clean:
	rm $(OBJ_DIR)/*.o $(TARGET) $(TEST_TARGET)
