CC = g++
FLAGS = -Wall -Werror

SOURCES = main.cpp car.cpp

all: simulator car.o

simulator: main.cpp car.o
	$(CC) $(FLAGS) -o $@ $^

car.o: car.cpp car.hpp
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf simulator
	rm -rf car.o

.PHONY: clean
