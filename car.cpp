#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "car.hpp"

Car::Car(){
    //std::srand(0);
    //std::rand();
    top_speed = 1667;       // cm/s
    top_acceleration = 449; // cm/s2
    car_length = 2500;      // cm
    current_speed = 0;
    current_position = 0;
    current_acceleration = 0;
    lane = 0;
}

float Car::get_top_speed(){
    return top_speed;
}

float Car::get_top_acceleration(){
    return top_acceleration;
}

float Car::get_speed(){
    return current_speed;
}

float Car::get_acceleration(){
    return current_acceleration;
}

float Car::get_position(){
    return current_position;
}

void Car::set_speed(float speed){
    current_speed = speed;
}

void Car::set_position(float position){
    current_position = position;
}

void Car::set_acceleration(float acceleration){
    current_acceleration = acceleration;
}

void Car::set_lane(unsigned char new_lane){
    lane = new_lane;
}
