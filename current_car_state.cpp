#include <iostream>

#include "current_car_state.hpp"

CarState::CarState(float position, float speed, float acceleration, unsigned int lane){
    this->speed = speed;
    this->position = position;
    this->acceleration = acceleration;
    this->lane = lane;
}

float CarState::get_position(){
    return position;
}

float CarState::get_speed(){
    return speed;
}

float CarState::get_acceleration(){
    return acceleration;
}

unsigned int CarState::get_lane(){
    return lane;
}

void CarState::print_state(){
	std::cout << "x= " << position
              << " v= " << speed
              << " a= " << acceleration
              << " lane= " << lane <<std::endl;
}
