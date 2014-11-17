#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#include "car.hpp"

const float PI = 3.14159265359;
std::pair<std::vector<Car>, std::vector<Car> > transition_function(Car state);

int main(){
    std::cout << "hello world" << std::endl;
    return 0;
}

std::pair<std::vector<Car>, std::vector<Car> > transition_function(Car state){
    std::pair<std::vector<Car>, std::vector<Car> > result;
    float x = state.get_speed() / state.get_top_speed();
    int top_acceleration = (int)(state.get_top_acceleration()*std::cos(x*(PI/2)));

    // acceleration
    int acceleration = (int) state.get_acceleration();
    for(; acceleration < top_acceleration; acceleration++){
        Car new_state(state);
        // time = 1 second
        float new_speed = state.get_speed() + acceleration;
        float new_position = state.get_position() + state.get_speed() + 0.5*acceleration;
        new_state.set_speed(new_speed);
        new_state.set_position(new_position);
        new_state.set_acceleration(acceleration);
        // TODO: lane
        result.first.push_back(new_state); 
    }

    // TODO: deceleration

    return result;
}

