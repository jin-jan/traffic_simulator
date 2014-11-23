#include "current_car_state.hpp"

CarState::CarState(float position, float speed, float acceleration, unsigned char lane){
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

unsigned char CarState::get_lane(){
    return lane;
}
