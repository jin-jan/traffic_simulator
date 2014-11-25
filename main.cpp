#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits>
#include <deque>

#include "car.hpp"
#include "traffic_simulator.hpp"
#include "current_car_state.hpp"

/*
Rationale of the default configuration:
top_speed          =   60 km/h
                   = 1667 cm/s
    Defined by the law of ZMG

top_acceleration   =  449 cm/s2
    Available performance measure states that the time it takes to accelerate
    from 0 to 97 km/h takes 6 seconds

car_length         =  400 cm
    Medium-sized cars approach 4.8 metres and often exceed this.
    In the simulation we considered +/- 100 cm to include small and large sized
    cars

total_cars         = 2500
    Random initialization of cars

lane               =    2
    Av. Lopez Mateos has two main lanes

goal_distance      =   10.4 km
    The simulation starts in the intersection between Periferico Sur and
    Av. Lopez Mateos and ends in the intersection between Av. Americas and
    Av. Lopez Materos

total_sem          =    0
    WIP

sem_sim            =    0
    WIP: simulation of different sempaphore algorithms

total_pot          =    0
    WIP
*/

void helpOutput(void)
{
    std::cout << "traffic simulation\n"
                 "USAGE: simulation [OPTIONS]\n"
                 "OPTIONS:\n"
                 "-c CARS    Set the number of CARS to simulate\n"
                 "-s SPEED   Set the maximun SPEED (km/h)\n"
                 "-d GOAL    Set the goal distance km\n"
                 "-l LANE    Set the number of lanes\n"
                 "-t LIGHT   Set the number of traffic LIGHTs to simulate\n"
                 "-p POTHELE Set the number of POTHELEs to simulate\n"
                 "-h         Display the help information\n" << std::endl;
}

void defaultConfig(void)
{
    std::cout << "Default configuration:\n"
                 "    number of cars:      2500\n"
                 "    car length:           400 cm\n"      //car_length
                 "    max speed:             60 km/h\n"    //top_speed
                 "    max acceleration:     449 cm/s2\n"   //top_acceleration
                 "    number of semaphores:   0\n"
                 "    semaphore simulation:   0\n"
                 "    number of potheles:     0\n"
                 "    goal distance:         10.4km\n"
                 "    lane:                   2\n"
                     <<  std::endl;
    exit(EXIT_FAILURE);
}

void switch_lane(Car &car, std::deque<Car>& lane){
    std::deque<Car> slower_cars;

    if (lane.empty())
        lane.push_back(car);
    else{
        while(!lane.empty()){
            Car last_car = lane.back();
            if(car.get_position() < last_car.get_position()){
                break;
            }else{
                slower_cars.push_back(last_car);
                lane.pop_back();
            }
        }

        lane.push_back(car);
        while(!slower_cars.empty()){
            lane.push_back(slower_cars.back());
            slower_cars.pop_back();
        }
    }
}


int search_car(Car &car, std::deque<Car> &lane, Car **front){
    std::deque<Car>::iterator car_in_lane;

    if(lane.empty()){
        *front = NULL;
        return 0;
    }


    if(car.get_position() <= lane.back().get_position()){
        *front = &(lane.back());
        return 0;
    }

    if(car.get_position() > lane.front().get_position()){
        front = NULL;
        return 0;
    }

    for(car_in_lane = lane.end(); car_in_lane != lane.begin(); --car_in_lane){
        if(car.get_position() < car_in_lane->get_position()){
            *front = &(*car_in_lane);
            break;
        }
    }

    return 0;
}

int search_car(Car &car, std::deque<Car> &lane, Car ***back, Car ***front){
    std::deque<Car>::iterator car_in_lane;

    if(car.get_position() <= lane.back().get_position()){
        back = NULL;
        **front = &(lane.back());
        return 0;
    }

    if(car.get_position() > lane.front().get_position()){
        **back = &(lane.front());
        front = NULL;
        return 0;
    }

    for(car_in_lane = lane.end(); car_in_lane != lane.begin(); --car_in_lane){
        if(car.get_position() < car_in_lane->get_position()){
            **front = &(*car_in_lane);
            **back = &(*(--car_in_lane));
            break;
        }
    }

    return 0;
}


int get_future_cars_in_lane(Car &car, std::deque<Car> &front_lane, std::deque<Car> &back_lane, Car **back, Car **front){

    if(front_lane.empty() && back_lane.empty()){
        back = NULL;
        front = NULL;
        return 0;
    }

    if(front_lane.empty() && !back_lane.empty()){
        search_car(car, back_lane, &back, &front);
        return 0;
    }

    if(!front_lane.empty() && back_lane.empty()){
        search_car(car, front_lane, &back, &front);
        return 0;
    }

    bool faser_than_slowers = car.get_position() >= back_lane.front().get_position();
    bool slower_than_fasters = car.get_position() < front_lane.back().get_position();
    if(faser_than_slowers && slower_than_fasters){
        *back = &back_lane.front();
        *front = &front_lane.back();
        return 0;
    }

    if(car.get_position() <  back_lane.back().get_position()){
        search_car(car, back_lane, &back, &front);
        return 0;
    }

    if(faser_than_slowers && !slower_than_fasters){
        search_car(car, front_lane, &back, &front);
        return 0;
       // search in front lane
    }

    if(!faser_than_slowers && slower_than_fasters){
        search_car(car, back_lane, &back, &front);
        return 0;
       // search in back lane
    }

    if(!faser_than_slowers && !slower_than_fasters){
        std::cerr << "ERROR: It seems lanes are not in the right order" << std::endl;
        std::exit(-1);
    }
    return -1;
}

void car_simulation(std::deque<Car> &lane0, std::deque<Car> &lane1)
{
	std::deque<Car> future_lane0;
	std::deque<Car> future_lane1;

    for(int i=0; i<50; i++){
        std::cout << i << ": " << std::endl;
        while(!lane0.empty() || !lane1.empty()){
            std::pair<std::vector<Car>, std::vector<Car> > next_states;

            if(!lane0.empty()){
                Car car = lane0.front();
                lane0.pop_front();
                Car *in_front = NULL;
                search_car(car, future_lane0, &in_front);

                Car *future_in_front = NULL;
                Car *future_in_back = NULL;
                get_future_cars_in_lane(car, future_lane1, lane1, &future_in_back, &future_in_front);

                next_states = transition_function(car);
                CarState new_state = heuristic(next_states.first,
                                               &car,
                                               in_front,
                                               future_in_front,
                                               future_in_back);
                car.set_car_state(new_state);
                if(new_state.get_lane() == 0)
                    future_lane0.push_back(car);
                else
                    switch_lane(car, future_lane1);
                    //future_lane1.push_back(car);
                car.print_state();
            }

            if(!lane1.empty()){
                Car car = lane1.front();
                lane1.pop_front();
                Car *in_front = NULL;
                search_car(car, future_lane1, &in_front);

                Car *future_in_front = NULL;
                Car *future_in_back = NULL;
                get_future_cars_in_lane(car, future_lane0, lane0, &future_in_back, &future_in_front);

                next_states = transition_function(car);
                CarState new_state = heuristic(next_states.first,
                                               &car,
                                               in_front,
                                               future_in_front,
                                               future_in_back);
                car.set_car_state(new_state);
                if(new_state.get_lane() == 0)
                    switch_lane(car, future_lane0);
                    //future_lane0.push_back(car);
                else
                    future_lane1.push_back(car);
                car.print_state();
            }

        }
    // prepare for next iteration
    lane0 = future_lane0;
    lane1 = future_lane1;
    future_lane0.clear();
    future_lane1.clear();
    }
}


int main(int argc, char **argv){
    int opt;
    float set_speed         =   60; //top_speed
    float set_goal_distance =   10.4; //goal_distance
    int set_lane            =    0; //lane
    unsigned char num_sem   =    0;
    unsigned char num_po    =    0;
    int num_cars  = 2500;

    while ((opt = getopt(argc, argv, "hc:s:d:l:t:p:")) !=  -1)
    {
        switch (opt)
        {
            case 'h':
                helpOutput();
                defaultConfig();
                break;
            case 'c':
                num_cars = static_cast<unsigned char>(*optarg);
                std::cout << "-c  " << num_cars << std::endl;
                break;
            case 's':
                set_speed = atof(optarg);
                std::cout << "-s " << set_speed << std::endl;
                break;
            case 'd':
                set_goal_distance = atof(optarg);
                std::cout << "-d " << set_goal_distance << std::endl;
                break;
            case 'l':
                set_lane = atoi(optarg);
                std::cout << "-l " << set_lane << std::endl;
                break;
            case 't':
                num_sem = static_cast<unsigned char>(*optarg);
                std::cout << "-t" << num_sem << std::endl;
                break;
            case 'p':
                num_po = static_cast<unsigned char>(*optarg);
                std::cout << "-p " << num_po << std::endl;
                break;
            default:
                fprintf(stderr, "Usage: %s [-c] [-s] [-d] [-l] [-t] [-p] [-h]",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    std::deque<Car> lane0;
    std::deque<Car> lane1;
    Car slow(20, 10, 0);
    Car fast(40, 10, 0);
    Car m(60, 10, 0);
    Car n(60, 10, 1);
    Car z(40, 10, 1);

    slow.print_state();
    fast.print_state();
    m.print_state();
    n.print_state();
    z.print_state();

    lane0.push_back(slow);
    lane0.push_back(fast);
    lane0.push_back(m);
    lane1.push_back(n);
    lane1.push_back(z);

    car_simulation(lane0, lane1);

    return 0;
}
