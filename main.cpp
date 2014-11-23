#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits>

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


void car_simulation(float top_speed,
                    float goal_distance,
                    char lane)
{

    Car a_car(top_speed, goal_distance, lane);
    std::pair<std::vector<Car>, std::vector<Car> > next_states;

    for(int i=0; i<5; i++){

        next_states = transition_function(a_car);

        auto iter = next_states.first.begin();
        auto end = next_states.first.end();
        for(;iter != end; iter++){
            std::cout << "x=" << iter->get_position()
                      << " v=" << iter->get_speed()
                      << " a=" << iter->get_acceleration() << std::endl;
        }
        
        CarState new_state = heuristic(next_states.first);
        std::cout << std::endl
                  << "best option:" << std::endl
                  << "x=" << new_state.get_position()
                  << " v=" << new_state.get_speed()
                  << " a=" << new_state.get_acceleration() << std::endl;

        a_car.set_state( new_state.get_position(),
                         new_state.get_speed(),
                         new_state.get_acceleration());
    }

    CarState new_state = heuristic(next_states.first);
    std::cout << std::endl
              << "best option:" << std::endl
              << "x=" << new_state.get_position()
              << " v=" << new_state.get_speed()
              << " a=" << new_state.get_acceleration() << std::endl;
    std::cout.precision(5);
    std::cout << "get_top_speed:" << a_car.get_top_speed() << "\n"
              << "get_goal_distance:" << a_car.get_goal_distance() << "\n"
              << "get_lane:" <<  a_car.get_lane() << "\n" << std::endl;
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
    car_simulation(set_speed,
                   set_goal_distance,
                   set_lane);

    return 0;
}
