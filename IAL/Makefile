CC = gcc
FLAGS=-Wall -Werror -Wextra -g
FILES = src/*.c src/*.h
COMPILED=ial

build:
	$(CC) $(FLAGS) $(FILES) -o $(COMPILED)

docs:
	doxygen Doxyfile

run: build
	./$(COMPILED) < tests/good_tests/input_10000.txt


clean:
	rm ial
