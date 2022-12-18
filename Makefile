MAZE_TEST_SRC:=tests/maze/maze_test.cc
MAZE_TEST_CLASS:=tests/maze/maze_test_class.cc
MAZE_SRC:=src/model/maze/maze.cc src/model/maze/answer/maze_answer.cc \
	src/model/maze/creating/maze_from_file.cc \
	src/model/maze/creating/maze_generation.cc 
CC:=gcc
COMP_FLAGS:=-lstdc++ -std=c++17 -Wall -Werror -Wextra -lm 
TEST_FLAGS:=-lgtest -pthread
DEBUG_FLAGS:=-g
MAZE_TESTS:=maze_tests

clean:
	rm -rf ./$(MAZE_TESTS)

build: clean
	$(CC) $(MAZE_TEST_SRC) $(MAZE_SRC) $(MAZE_TEST_CLASS) $(SRC) $(COMP_FLAGS) $(TEST_FLAGS) -o $(MAZE_TESTS)

tests: build
	./$(MAZE_TESTS)
	rm -rf $(MAZE_TESTS)
