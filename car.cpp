#include <string>
#include <vector>
#include <cmath>

#include "car.hpp"

Car::Car(float top_speed,
         float goal_distance,
         int lane){

    this->top_speed = (top_speed*1000)/36;         // cm/s
    this->top_acceleration = 449;     // cm/s2
    this->car_length = 400;                        // cm
    this->goal_distance = goal_distance*(100000);  // cm
    this->lane = lane;
    current_speed = 0;
    current_position = 0;
    current_acceleration = 0;
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

float Car::get_car_length(){
    return car_length;
}

float Car::get_goal_distance(){
    return goal_distance;
}

float Car::get_lane(){
    return lane;
}

float Car::get_rear_position(){
    return current_position-car_length;
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

void Car::set_state(float position, float speed, float acceleration){
    current_position = position;
    current_speed = speed;
    current_acceleration = acceleration;
}

void Car::set_top_speed(float new_top_speed){
    top_speed = new_top_speed;
}

void Car::set_car_length(float new_length){
    car_length = new_length;
}

void Car::set_goal_distance(float new_distance){
    goal_distance = new_distance;
}
