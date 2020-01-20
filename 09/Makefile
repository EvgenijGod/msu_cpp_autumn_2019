CC=g++

all: my_prog

my_prog: main.o sort.o
	$(CC) -pthread -o my_prog main.o sort.o

main.o: main.cpp sort.h
	$(CC) -pthread -c -O2 --std=c++17 main.cpp

sort.o: sort.cpp
	$(CC) -pthread -c -O2 --std=c++17 sort.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog