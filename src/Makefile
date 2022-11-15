SRC:=model/cave.cc
CC:=gcc
COMP_FLAGS:=-lstdc++ -std=c++17 -Wall -Werror -Wextra
DEBUG_FLAGS:=-g

clean:
	rm -rf a.out*

build: clean
	$(CC) $(COMP_FLAGS) $(SRC) test.cc

test: build
	./a.out

debug:
	$(CC) $(COMP_FLAGS) $(DEBUG_FLAGS) $(SRC) test.cc

leaks: build
	leaks -atExit -- ./a.out

docker:
	cd ../materials/build && bash run.sh

style_test:
	cp ../materials/linters/.clang-format .
	clang-format -n model/*.cc model/*.h helpers/*.h
	rm -rf .clang-format