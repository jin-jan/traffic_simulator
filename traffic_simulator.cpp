#include <vector>
#include <map>
#include <cmath>
#include <deque>
#include <iostream>
#include <stdlib.h>

#include "car.hpp"
#include "current_car_state.hpp"

const float PI = 3.14159265359;

CarState heuristic(std::vector<Car>& acc_states)
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
    */

    std::pair<float, CarState> best_state = std::make_pair(0.0, CarState(0.0, 0.0, 0.0));
    for(std::vector<Car>::iterator state = acc_states.begin(); state != acc_states.end(); state++){
        //float distance_to_next_car;
        float position = state->get_position();
        float speed = state->get_speed() / state->get_top_speed();

        float weight = 0.30*position + 0.10*speed;
        //float weight = 0.35 + 0.30 + 0.20 + 0.10 + 0.05;

        if(weight > best_state.first){
            best_state.first = weight;
            best_state.second = CarState(state->get_position(), state->get_speed(), state->get_acceleration());
        }
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

void init_car_population (std::deque<Car>& lane0,
                          std::deque<Car>& lane1,
                          float set_speed,
                          float set_start_distance,
                          float set_goal_distance,
                          float num_cars){
    int craziness_speed;
    float sane = 0.75;
    float insane = 0.1;
    float crazy = 0.15;
    float car_sane = 0;
    float car_insane = 0;
    float car_crazy = 0;
    float total_sane, total_insane, total_crazy, rand_id_entr, rand_id_exit;
    total_sane   = num_cars*sane;
    total_insane = num_cars*insane;
    total_crazy  = (num_cars*crazy)-1;


    float entrance_allowed[] = {0,
                                110000,
                                220000,
                                327100,
                                490000,
                                540000,
                                629000,
                                710000,
                                993000,
                                1000000};
    float entrance_prohibited[] = { 75000,
                                    85000,
                                    322100,
                                    350000,
                                    470000,
                                    480000,
                                    500000,
                                    510000,
                                    942700,
                                    950000,
                                    978500,
                                    988300,
                                    1015000};
    float exit_allowed[] = {100000,
                            130000,
                            200000,
                            290000,
                            460600,
                            510000,
                            745000,
                            810000,
                            890000,
                            971100,
                            1020000,
                            1040000};
    float exit_prohibited[] = { 75000,
                                85000,
                                322100,
                                350000,
                                470000,
                                480000,
                                500000,
                                942700,
                                950000,
                                978500,
                                988300,
                                1015000};

    std::vector<float> entr_all_vector (entrance_allowed, entrance_allowed + sizeof(entrance_allowed)/sizeof(float));
    std::vector<float> entr_pro_vector (entrance_prohibited, entrance_prohibited + sizeof(entrance_prohibited)/sizeof(float));
    std::vector<float> exit_all_vector (exit_allowed, exit_allowed + sizeof(exit_allowed)/sizeof(float));
    std::vector<float> exit_pro_vector (exit_prohibited, exit_prohibited + sizeof(exit_prohibited)/sizeof(float));
    std::vector<float> entrance;
    entrance.reserve(entr_all_vector.size() + entr_pro_vector.size());
    entrance.insert(entrance.end(), entr_all_vector.begin(), entr_all_vector.end());
    entrance.insert(entrance.end(), entr_pro_vector.begin(), entr_pro_vector.end());
    std::vector<float> exit;
    exit.reserve(exit_all_vector.size() + exit_pro_vector.size());
    exit.insert(exit.end(), exit_all_vector.begin(), exit_all_vector.end());
    exit.insert(exit.end(), exit_pro_vector.begin(), exit_pro_vector.end());

    while( (car_sane < total_sane) ){
        craziness_speed = (rand() % 100 + 1);
        rand_id_entr = rand() % entrance.size();
        rand_id_exit = rand() % exit.size();

        if ( (car_sane < total_sane) && (craziness_speed < set_speed && craziness_speed > crazy*100)){
            Car new_car(car_sane, entrance[rand_id_entr],exit[rand_id_exit]);
            car_sane++;
        }else if ((car_insane < total_insane) && (craziness_speed > set_speed)){
            Car new_car(car_insane, entrance[rand_id_entr], exit[rand_id_exit]);
            car_insane++;
        }else if ( (car_crazy <= total_crazy) && (craziness_speed < crazy * 100)){
            Car new_car(car_crazy, entrance[rand_id_entr], exit[rand_id_exit]);
            car_crazy++;
        lane0.push_back(new_car);
        lane1.push_front(new_car);
        }
    }
}