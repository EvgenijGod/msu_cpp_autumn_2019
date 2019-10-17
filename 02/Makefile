CC=g++

all: my_prog

my_prog: main.o test.o Timer.o
	$(CC) -o my_prog main.o test.o Timer.o

main.o: main.cpp
	$(CC) -c -O2 -std=c++14 main.cpp

test.o: test.cpp
	$(CC) -c -O2 -std=c++14 test.cpp

Timer.o: Timer.cpp
	$(CC) -c -O2 -std=c++14 Timer.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog