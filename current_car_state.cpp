#include "current_car_state.hpp"

CarState::CarState(float position, float speed, float acceleration){
    this->speed = speed;
    this->position = position;
    this->acceleration = acceleration;
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
