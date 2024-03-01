CC := clang
CFLAGS := -g -Wall -Wextra -I/opt/homebrew/Cellar/allegro/5.2.9.1/include -Iinclude
# Define library paths in addition to /usr/lib
LDFLAGS = -L/opt/homebrew/Cellar/allegro/5.2.9.1/lib

SRC_DIR := src
OBJ_DIR := bin
BIN_DIR := bin

# Define any libraries to link into executable:
LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf

# Define the C source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET := $(BIN_DIR)/tictactoe

TEST_DIR := tests
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_SRC_FILES := $(filter-out src/main.c, $(SRC_FILES))
TEST_TARGET := $(BIN_DIR)/test_runner

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ_FILES) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/*.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_TARGET): $(TEST_DIR)/test_runner.c $(TEST_SRC_FILES) $(TEST_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: tests
tests: $(TEST_TARGET)

# Rule to run the tests
test: tests
	./bin/test_runner

.PHONY: clean
clean:
	rm $(OBJ_DIR)/*.o $(TARGET) $(TEST_TARGET) 
