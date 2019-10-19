CC=g++

all: my_prog

my_prog: main.o allocator.o Timer.o
	$(CC) -o my_prog main.o allocator.o Timer.o

main.o: main.cpp allocator.h Timer.h
	$(CC) -c -O2 -std=c++14 main.cpp

allocator.o: allocator.cpp
	$(CC) -c -O2 -std=c++14 allocator.cpp

Timer.o: Timer.cpp
	$(CC) -c -O2 -std=c++14 Timer.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog