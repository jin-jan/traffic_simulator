#ifndef CAR_H
#define CAR_H

class Car{
    public:
        Car();
        float get_top_speed();
        float get_top_acceleration();
        float get_speed();
        float get_acceleration();
        float get_position();
        void set_speed(float speed);
        void set_position(float position);
        void set_acceleration(float acceleration);
        void set_lane(unsigned char new_lane);
        void set_state(float position, float speed, float acceleration);

    private:
        unsigned int id;
        unsigned int top_speed;              // in cm/s
        float top_acceleration;
        unsigned int car_length;             // in cm
        float current_speed;
        float current_position;
        float current_acceleration;
        unsigned char lane;
};

#endif
