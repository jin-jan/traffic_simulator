CC = g++
FLAGS = -Wall -Werror -std=c++0x

SOURCES = main.cpp car.cpp

all: simulator car.o traffic_simulator.o traffic_simulator.o

simulator: main.cpp car.o traffic_simulator.o current_car_state.o car.o
	$(CC) $(FLAGS) -o $@ $^

car.o: car.cpp car.hpp
	$(CC) $(FLAGS) -c $<

current_car_state.o: current_car_state.cpp current_car_state.hpp
	$(CC) $(FLAGS) -c $<

traffic_simulator.o: traffic_simulator.cpp traffic_simulator.hpp current_car_state.o
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf simulator
	rm -rf *.o

.PHONY: clean
