CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRCS = src/main.c src/cli.c src/scanner.c src/reader.c src/chunker.c

TARGET = askie

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)