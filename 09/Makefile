CC=g++

all: my_prog

my_prog: main.o sort.h
	$(CC) -pthread -o my_prog main.o sort.h

main.o: main.cpp sort.h
	$(CC) -pthread -c -O2 --std=c++17 main.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog