CAVE_TEST_SRC:=cave_test.cc
CAVE_SRC:=../../src/model/cave/cave.cc moc_generator.cc
CC:=gcc
COMP_FLAGS:=-lstdc++ -std=c++17 -Wall -Werror -Wextra -lm 
TEST_FLAGS:=-lgtest -pthread
DEBUG_FLAGS:=-g
CAVE_TESTS:=cave_tests

clean:
	rm -rf ./$(CAVE_TESTS)

build: clean
	$(CC) $(CAVE_TEST_SRC) $(CAVE_SRC) \
	$(DEBUG_FLAGS) $(COMP_FLAGS) $(TEST_FLAGS) -o $(CAVE_TESTS)

tests: build
	./$(CAVE_TESTS)
	rm -rf $(CAVE_TESTS)
