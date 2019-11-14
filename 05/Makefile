CC=g++

all: my_prog

my_prog: main.o serializer.o
	$(CC) -o my_prog main.o serializer.o

main.o: main.cpp serializer.h
	$(CC) -c -O2 -std=c++14 main.cpp

serializer.o: serializer.cpp
	$(CC) -c -O2 -std=c++14 serializer.cpp

test:
	./my_prog

clean:
	rm -rf *.o my_prog