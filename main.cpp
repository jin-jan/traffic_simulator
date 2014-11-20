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
                         "    number of cars:       2500\n"         //car_length
                     "    max speed:            1667 cm/s\n"    //top_speed
                     "    max acceleration:     449 cm/s2\n"  //top_acceleration
                     "    number of semaphores:   0\n"
                     "    semaphore simulation:   0\n"
                     "    number of potheles:     0\n"
                     <<  std::endl;
    exit(EXIT_FAILURE);
}

void carSim(void)
{
    Car a_car;
    std::pair<std::vector<Car>, std::vector<Car> > next_states;

    next_states = transition_function(a_car);

    auto iter = next_states.first.begin();
    auto end = next_states.first.end();
    for(;iter != end; iter++){
        std::cout << "x= " << iter->get_position()
                  << "v= " << iter->get_speed()
                  << "a= " << iter->get_acceleration() << std::endl;
    }
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

    return 0;
}
