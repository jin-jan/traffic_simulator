#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "car.hpp"
#include "current_car_state.hpp"

const float PI = 3.14159265359;

/********************************
 * internal only functions
 *******************************/
float get_safe_distance(float speed){
    if (speed == 0.0)
        return 100;

    // otherwise use 2 seconds rule
    return 2*speed;
}

bool car_crashes(Car *current, Car *in_front){
	if (in_front == NULL || current == NULL)
		return false;

    float distance_to_car = in_front->get_rear_position()-current->get_position();
    return (distance_to_car < get_safe_distance(current->get_speed()));
}

bool is_safe_change_lane(Car *in_back, Car *current, Car *in_front){
    if (in_back == NULL && in_front == NULL)
        return true;

    if (in_back == NULL)
        return !car_crashes(current, in_front);

    if (in_front == NULL)
        return !car_crashes(in_back, current);

    if (!car_crashes(current, in_front) && !car_crashes(in_back, current))
        return true;
    else
        return false;
}

bool is_pothole_in_range(){
    return false;
}


bool is_exit_in_range(){
    return false;
}
/********************************
 * External interface
 *******************************/
CarState heuristic(std::vector<Car>& new_states,
                   Car *car,
                   Car *car_in_front_current,
                   Car *car_in_front,
                   Car *car_in_back)
{
    /*
    TODO: add pothele heuristic
    */
    if (new_states.empty()){
        std::cerr << "ERROR: there are no new states" << std::endl;
        std::exit(-1);
    }

    std::pair<float, CarState> best_state = std::make_pair(-100000.0, CarState(0.0, 0.0, 0.0, 0));
    for(std::vector<Car>::iterator state = new_states.begin(); state != new_states.end(); state++){
        bool stay_in_current_lane = state->get_lane() == car->get_lane() ;
        bool exceed_top_speed = state->get_speed() > car->get_top_speed();
        float weight = 0.0;
        float factor = 1.0;
        float factor_change_lane = 1.0;
        float speed_ratio = 0.0;
        float position_ratio = 0.0;

        // make sure new state is "safe"
        if(state->get_position() < 0)
            continue;

        if(exceed_top_speed){
            continue;
        }

        if(stay_in_current_lane){
            if(car_crashes(&(*state), car_in_front_current)){
                if(car->get_position() == 0.0)
                    return car->get_state();
                continue;
            }
            else
                //extra points for staying in the same lane
                factor += 0.05;
        }else{
            if (!is_safe_change_lane(car_in_back, &(*state), car_in_front))
                continue;
            else
                //
                factor_change_lane -= 0.05;
        }

        speed_ratio = (factor_change_lane*state->get_speed()) / car->get_top_speed();
        position_ratio = state->get_position() / car->get_goal_distance();
        weight = factor*(speed_ratio+position_ratio);

        // is this state better than the previous one
        if(weight > best_state.first){
            best_state.first = weight;
            best_state.second = CarState(state->get_position(),
                                         (factor_change_lane*state->get_speed()),
                                         state->get_acceleration(),
                                         state->get_lane());
        }
    }

    if(best_state.first == -100000.0){
        std::cerr << "ERROR: heuristic unable to find a suitable state for "
                  << car->get_id()
                  << std::endl;
        std::exit(-1);
    }

    return best_state.second;
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

std::pair<std::vector<Car>, std::vector<Car>> transition_function(Car state){
    std::pair<std::vector<Car>, std::vector<Car>> result;
    float x = state.get_speed() / state.get_top_speed();
    int top_acceleration = (int)(state.get_top_acceleration()*std::cos(x*(PI/2)));
    int botton_acceleration = -700;

    for(int acceleration = botton_acceleration; acceleration < top_acceleration; acceleration++){
        Car new_state(state);
        // time = 1 second
        float new_speed = state.get_speed() + acceleration;
        float new_position = state.get_position() + state.get_speed() + 0.5*acceleration;
        new_state.set_speed(new_speed);
        new_state.set_position(new_position);
        new_state.set_acceleration(acceleration);

        new_state.set_lane(0);
        result.first.push_back(new_state);

        new_state.set_lane(1);
        result.first.push_back(new_state);
    }

    return result;
}
