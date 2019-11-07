CC=g++

all: my_prog

my_prog: main.o BigInt.o
	$(CC) -o my_prog main.o BigInt.o

main.o: main.cpp BigInt.h
	$(CC) -c -O2 -std=c++14 main.cpp

BigInt.o: BigInt.cpp
	$(CC) -c -O2 -std=c++14 BigInt.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog