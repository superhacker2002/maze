# maze testing
MAZE_TEST_SRC:=tests/maze/maze_test.cc
MAZE_TEST_CLASS:=tests/maze/maze_test_class.cc
MAZE_SRC:=src/model/maze/maze.cc \
	src/model/maze/answer/maze_answer.cc \
	src/model/maze/creating/maze_from_file.cc \
	src/model/maze/creating/maze_generation.cc \
	src/model/helpers/randomizer/generator.cc
MAZE_TESTS:=maze_tests

# cave testing
CAVE_TEST_SRC:=tests/cave/cave_test.cc
CAVE_SRC:=src/model/cave/cave.cc tests/cave/moc_generator.cc
CAVE_TESTS:=cave_tests

CC:=gcc
COMP_FLAGS:=-lstdc++ -std=c++17 -Wall -Werror -Wextra -lm 
TEST_FLAGS:=-lgtest -pthread
DEBUG_FLAGS:=-g

all: install clean

clean:
	make -C src/view clean
	rm -rf ./$(MAZE_TESTS)
	rm -rf ./$(CAVE_TESTS)

build_maze_tests: clean
	$(CC) $(MAZE_TEST_SRC) $(MAZE_SRC) $(MAZE_TEST_CLASS) \
	$(COMP_FLAGS) $(TEST_FLAGS) -o $(MAZE_TESTS)

build_cave_tests: clean
	$(CC) $(CAVE_TEST_SRC) $(CAVE_SRC) $(COMP_FLAGS) $(TEST_FLAGS) -o $(CAVE_TESTS)

tests: build_maze_tests build_cave_tests
	./$(MAZE_TESTS)
	./$(CAVE_TESTS)
	rm -rf $(MAZE_TESTS)
	rm -rf $(CAVE_TESTS)

install:
	make -C src/view install

uninstall:
	make -C src/view uninstall

dist:
	cd build && tar -zcf ../maze.tar.gz maze_and_cave.app

distclean:
	rm -rf maze.tar.gz

dvi:
	open dvi.html

leaks: build
	leaks -atExit -- ./$(MAZE_TESTS)
	leaks -atExit -- ./$(CAVE_TESTS)

docker:
	cd materials/build && bash run.sh

style_test:
	cp materials/linters/.clang-format .
	clang-format -n src/model/cave/* \
					src/model/drawing/* \
	 				src/model/maze/answer/* \
					src/model/maze/creating/* \
					src/model/maze/*.cc \
					src/model/maze/*.h \
					src/model/helpers/randomizer/* \
					src/model/helpers/*.h \
					src/view/*.cc \
					src/view/*.h \
					tests/maze/* \
					tests/cave/*
	rm -rf .clang-format
