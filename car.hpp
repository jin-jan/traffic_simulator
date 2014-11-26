#ifndef CAR_H
#define CAR_H

#include "current_car_state.hpp"

class Car{
    public:
        Car(float top_speed,
            unsigned int lane,
            float start_distance,
            float goal_distance);
        float get_top_speed();
        float get_top_acceleration();
        float get_speed();
        float get_acceleration();
        float get_position();
        float get_car_length();
        float get_goal_distance();
        unsigned int get_lane();
        float get_rear_position();
        unsigned int get_id();
        float get_start_distance();
        void set_speed(float speed);
        void set_position(float position);
        void set_acceleration(float acceleration);
        void set_lane(unsigned int new_lane);
        void set_state(float position, float speed, float acceleration);
        void set_top_speed(float new_top_speed);
        void set_car_length(float new_length);
        void set_goal_distance(float new_distance);
        void set_car_state(CarState &state);
        void print_state();
        void set_start_distance(float new_distance);
        CarState get_state();

    private:
        unsigned int id;
        float top_speed;              // in cm/s
        float top_acceleration;
        unsigned int car_length;             // in cm
        float current_speed;
        float current_position;
        float current_acceleration;
        unsigned int lane;
        float goal_distance;
        int get_unique_id();
        float start_distance;
};

#endif
