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