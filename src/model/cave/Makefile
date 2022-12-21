SRC:=cave.cc ../helpers/randomizer/generator.cc
CC:=gcc
COMP_FLAGS:=-lstdc++ -std=c++17 -Wall -Werror -Wextra -lm
DEBUG_FLAGS:=-g

clean:
	rm -rf a.out*

build: clean
	$(CC) $(SRC) test.cc $(COMP_FLAGS)

test: build
	./a.out

debug:
	$(CC) $(SRC) test.cc $(COMP_FLAGS) $(DEBUG_FLAGS)

leaks: build
	leaks -atExit -- ./a.out

docker:
	cd ../materials/build && bash run.sh

style_test:
	cp ../materials/linters/.clang-format .
	clang-format -n model/*.cc model/*.h helpers/*.h
	rm -rf .clang-format