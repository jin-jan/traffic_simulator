#ifndef CURRENT_STATE_H
#define CURRENT_STATE_H

class CarState{
    public:
        CarState(float position, float speed, float acceleration, unsigned int lane);
        float get_position();
        float get_speed();
        float get_acceleration();
        unsigned int get_lane();
        void print_state();
    
    private:
        float speed;
        float position;
        float acceleration;
        unsigned int lane;
};

#endif
