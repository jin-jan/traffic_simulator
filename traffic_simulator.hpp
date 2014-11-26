#include <vector>

#include "car.hpp"
#include "current_car_state.hpp"

#ifndef TRAFFIC_SIMULATOR_H
#define TRAFFIC_SIMULATOR_H

CarState heuristic(std::vector<Car>& new_states,
                   Car *car,
                   Car *car_in_front_current,
                   Car *car_in_front,
                   Car *car_in_back);
float transition();
float traffic_simulation();
std::pair<std::vector<Car>, std::vector<Car> > transition_function(Car state);
void init_car_population(std::deque<Car>& lane0,
                         std::deque<Car>& lane1,
                         float set_speed,
                         float num_cars);

#endif
