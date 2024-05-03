# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++17 -Wall

# Directories
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Create the directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Test source files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BINS = $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))

# Database
DATABASE = sqlite3

# Targets
all: $(BIN_DIR)/program_exec

test: $(TEST_BINS)
	@for test_bin in $(TEST_BINS); do \
        echo "Running test: $$test_bin"; \
        ./$$test_bin; \
    done

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR)/program_exec: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(DATABASE)

$(BIN_DIR)/%: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) -I$(INC_DIR) $< -o $@ -l$(DATABASE)

run: $(BIN_DIR)/program_exec
	./$(BIN_DIR)/program_exec

built: $(OBJS) $(BIN_DIR)/program_exec

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean test run built
