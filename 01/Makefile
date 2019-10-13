CC=g++
ARGS ?= default_args

all: my_prog

my_prog: main.o
	$(CC) -o my_prog main.o

main.o: main.cpp
	$(CC) -c -O2 -std=c++14 main.cpp

run: my_prog
	./my_prog $(ARGS)

test:
	python3 ./test.py

clean:
	rm -rf *.o my_prog