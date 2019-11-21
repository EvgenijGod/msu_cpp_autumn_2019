CC=g++

all: my_prog

my_prog: main.o Vector.h
	$(CC) -o my_prog main.o Vector.h

main.o: main.cpp Vector.h
	$(CC) -c -O2 -std=c++14 main.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog