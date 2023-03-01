NAME = s21_cat
CC = gcc -Wall -Werror -Wextra -std=c11
SOURSES = s21_cat.c
OBJECT = s21_cat.o
LIB = s21_cat.h

all: clean s21_cat

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME)

s21_cat.o: s21_cat.c
	$(CC) $(SOURSES) $(LIB) -c

rebuild:
	$(MAKE) clean
	$(MAKE) all

clean:
	rm -rf *.o *.gch *.out log.txt s21_cat

check: s21_cat
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
	cppcheck *.h *.c
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -n *.h
	rm .clang-format

test: t_cat.sh
	bash t_cat.sh
