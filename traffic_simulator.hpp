#include <vector>

#include "car.hpp"

#ifndef TRAFFIC_SIMULATOR_H
#define TRAFFIC_SIMULATOR_H

float heuristic(std::vector<Car>& acc_states);
float transition();
float traffic_simulation();
std::pair<std::vector<Car>, std::vector<Car> > transition_function(Car state);

#endif
