#ifndef CAR_H
#define CAR_H

class Car{
    public:
        Car(float top_speed,
            float goal_distance,
            int lane);
        float get_top_speed();
        float get_top_acceleration();
        float get_speed();
        float get_acceleration();
        float get_position();
        float get_car_length();
        float get_goal_distance();
        float get_lane();
        float get_rear_position();
        void set_speed(float speed);
        void set_position(float position);
        void set_acceleration(float acceleration);
        void set_lane(unsigned char new_lane);
        void set_state(float position, float speed, float acceleration);
        void set_top_speed(float new_top_speed);
        void set_car_length(float new_length);
        void set_goal_distance(float new_distance);

    private:
        unsigned int id;
        float top_speed;              // in cm/s
        float top_acceleration;
        unsigned int car_length;             // in cm
        float current_speed;
        float current_position;
        float current_acceleration;
        int lane;
        float goal_distance;
};

#endif
