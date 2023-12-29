CC = gcc
CFLAGS = -Wall

.PHONY: all debug run

all: todo

debug: CFLAGS += -g
debug: todo

test: todo
	./todo -f notes "my test"

clean:
	rm -f todo
