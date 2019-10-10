CC=g++

all: my_prog

my_prog: main.o Timer.o 
	$(CC) -o my_prog main.o Timer.o

main.o: main.cpp Timer.cpp
	$(CC) -c -O2 -std=c++14 main.cpp

Timer.o: Timer.cpp Timer.h
	$(CC) -c -O2 -std=c++14 Timer.cpp

run:
	./my_prog

clean:
	rm -rf *.o my_prog