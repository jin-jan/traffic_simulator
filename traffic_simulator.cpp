#include <vector>
#include <map>
#include <cmath>

#include "car.hpp"

const float PI = 3.14159265359;

float heuristic(std::vector<Car>& acc_states)
{
    /*
    TODO: add pothele heuristic

    Calculate new velocity
    Calculate new position
    Calculate new lane

    for all states
        if is_acc
            *a-distance to car in front           35%
                TODO: find relationship
            *b-total distance:                    30%
                x = x-actual/x-goal
            *c-relation % v-actual/x-goal         20%
                TODO: find relationship
            *d-velocity:                          10%
                v = v-actual/v-goal
            *e-lane                               5%
                TODO: find relationship
            *h = a? + bx + c? + e?
        else
            *a-distance to car in front           50%
               TODO: find relationship
            *b-velocity: v-actual/v-goal          30%
                v = v-actual/v-goal
            *c-lane                               20%
               TODO: find relationship
            *h = a? + bv + c?

    std::pair<float, Car *> best_option(0.0, nullptr);
    for(auto state: acc_states){
        float distance_to_next_car;
        float position = state.get_position() / state.get_goal_position();
        float d;
        float weight = 0.35 + 0.30 + 0.20 + 0.10 + 0.05;

    }
    */
    return 0.0;
}

float transition()
{
    /*
     TODO: investigate average acceleration
    */
    return 0.0;
}

float traffic_simulation()
{

    /*while not_last_car
        *Call transition function to calculte new possible states
        *Call heuristic_function to select best new state
        *Update current state
    Setup for next iteration (traffic lights, pothele)
    */
    return 0.0;
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
