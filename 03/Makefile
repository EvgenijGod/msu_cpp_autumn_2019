CC=g++

all: my_prog

my_prog: main.o Matrix.o
	$(CC) -o my_prog main.o Matrix.o

main.o: main.cpp Matrix.h
	$(CC) -c -O2 -std=c++14 main.cpp

Matrix.o: Matrix.cpp
	$(CC) -c -O2 -std=c++14 Matrix.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog