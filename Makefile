CC = g++
FLAGS = -Wall -Werror -std=c++11

SOURCES = main.cpp car.cpp

all: simulator car.o traffic_simulator.o

simulator: main.cpp car.o traffic_simulator.o
	$(CC) $(FLAGS) -o $@ $^

car.o: car.cpp car.hpp
	$(CC) $(FLAGS) -c $<

traffic_simulator.o: traffic_simulator.cpp traffic_simulator.hpp
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf simulator
	rm -rf car.o
	rm -rf traffic_simulator.o

.PHONY: clean
