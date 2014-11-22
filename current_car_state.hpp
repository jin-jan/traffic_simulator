#ifndef CURRENT_STATE_H
#define CURRENT_STATE_H

class CarState{
    public:
        CarState(float position, float speed, float acceleration);
        float get_position();
        float get_speed();
        float get_acceleration();
    
    private:
        float speed;
        float position;
        float acceleration;
};

#endif
