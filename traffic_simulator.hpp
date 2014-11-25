#include <vector>

#include "car.hpp"
#include "current_car_state.hpp"

#ifndef TRAFFIC_SIMULATOR_H
#define TRAFFIC_SIMULATOR_H

CarState heuristic(std::vector<Car>& acc_states);
float transition();
float traffic_simulation();
std::pair<std::vector<Car>, std::vector<Car> > transition_function(Car state);
void init_car_population(std::deque<Car>& lane0,
                         std::deque<Car>& lane1,
                         float set_speed,
                         float set_start_distance,
                         float set_goal_distance,
                         float num_cars);

#endif
