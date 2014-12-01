CC = gcc
EXTRA_FLAGS = -fopenmp -lm -g

all: parallel_simulator

parallel_simulator: parallel_simulator.c
	$(CC) -o $@ $^ $(EXTRA_FLAGS)

parallel_simulator_mic: parallel_simulator.c
	$(CC) -o $@ $^ $(EXTRA_FLAGS) -mmic


clean:
	rm -rf parallel_simulator parallel_simulator_mic

.PHONY: clean
