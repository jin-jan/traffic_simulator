#ifndef CURRENT_STATE_H
#define CURRENT_STATE_H

class CarState{
    public:
        CarState(float position, float speed, float acceleration, unsigned char lane);
        float get_position();
        float get_speed();
        float get_acceleration();
        unsigned char get_lane();
    
    private:
        float speed;
        float position;
        float acceleration;
        unsigned char lane;
};

#endif
