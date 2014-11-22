#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

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
                 "-s SPEED   Set the maximun SPEED (cm/s)\n"
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


void carSim(void)
{
    Car a_car(60, 449, 4000, 10, 0);
    std::pair<std::vector<Car>, std::vector<Car> > next_states;

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
}

int main(int argc, char **argv){
    int opt;
    char *num_cars, *num_sem, *num_po, *set_speed;

    while ((opt = getopt(argc, argv, "hc:s:t:p:")) !=  -1)
    {
        switch (opt)
        {
            case 'h':
                helpOutput();
                defaultConfig();
                break;
            case 'c':
                num_cars = optarg;
                std::cout << "c value: " << num_cars << std::endl;
                break;
            case 's':
                set_speed = optarg;
                std::cout << "s value:" << set_speed << std::endl;
                break;
            case 't':
                num_sem = optarg;
                std::cout << "t value:" << num_sem << std::endl;
                break;
            case 'p':
                num_po = optarg;
                std::cout << "p value" << num_po << std::endl;
                break;
            default:
                fprintf(stderr, "Usage: %s [-c] [-s] [-t] [-p] [-h]", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    carSim();
    return 0;
}
