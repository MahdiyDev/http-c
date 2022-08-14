CC=gcc
ERR=-Wall -Wpedantic -Werror

install:
	$(CC) --static main.c -o main $(ERR)
