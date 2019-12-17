CC=g++

all: my_prog

my_prog: main.o Thread.h
	$(CC) -pthread -o my_prog main.o Thread.h

main.o: main.cpp Thread.h
	$(CC) -pthread -c -O2 --std=c++17 main.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog