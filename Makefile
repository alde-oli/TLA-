LIB_NAME = libtla.a
TEST_BIN = test_suite

INCLUDE_DIR = inc
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCLUDE_DIR) -O2 -march=native -fopenmp
LDFLAGS = -L. -ltla


SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_FILES))



all: $(LIB_NAME) $(TEST_BIN)

$(LIB_NAME): $(OBJ_FILES)
	@echo "Creating library $(LIB_NAME)..."
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: $(TEST_BIN)
	@echo "Executing tests..."
	./$(TEST_BIN)

$(TEST_BIN): $(LIB_NAME) $(TEST_OBJ_FILES)
	@echo "Compiling test binary $(TEST_BIN)..."
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling test file $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	@echo "Cleaning objs and binaries..."
	rm -rf $(OBJ_DIR)/*.o $(LIB_NAME) $(TEST_BIN)

fclean: clean
	@echo "Full clean..."
	rm -rf $(OBJ_DIR)

re: clean all

.PHONY: all test clean fclean re
