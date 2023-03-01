OS := $(shell uname -s)

ifeq ($(OS), Drawin)
 CC += -D OS_MAC
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
endif

CC = gcc -Wall -Werror -Wextra -std=c11

all: clean s21_grep clear

s21_grep: s21_grep.o
	$(CC) -o s21_grep s21_grep.o

s21_grep.o: s21_grep.c
	$(CC) -c s21_grep.c

test: t_grep.sh
	bash t_grep.sh

test1: s21_test_grep.sh
	bash s21_test_grep.sh

check:
	cppcheck *.h *.c
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -n *.h
	rm .clang-format

clean:
	rm -rf *.o
	rm -rf s21_grep
	rm -rf log.txt
	rm -rf RESULT_VALGRIND.txt

clear:
	clear

