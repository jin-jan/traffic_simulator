#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#include "car.hpp"
#include "traffic_simulator.hpp"

int main(){
    std::cout << "hello world" << std::endl;
    Car a_car;
    std::pair<std::vector<Car>, std::vector<Car> > next_states;

    next_states = transition_function(a_car);

    auto iter = next_states.first.begin();
    auto end = next_states.first.end();
    for(;iter != end; iter++){
        std::cout << "x= " << iter->get_position()
                  << " v= " << iter->get_speed()
                  << " a= " << iter->get_acceleration() << std::endl;
    }

    return 0;
}
