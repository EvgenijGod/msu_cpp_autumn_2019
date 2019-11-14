CC=g++

all: my_prog

my_prog: main.o
	$(CC) -o my_prog main.o

main.o: main.cpp
	$(CC) -c -O2 -std=c++14 main.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog