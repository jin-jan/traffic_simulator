
float heuristic(State *acc_state, State *dec_state)
{
    /*
    TODO: add pothele heuristic

    Calculate new velocity
    Calculate new position
    Calculate new lane

    for all states
        if is_acc
            *a-distance to car in front           35%
                TODO: find relationship
            *b-total distance:                    30%
                x = x-actual/x-goal
            *c-relation % v-actual/x-goal         20%
                TODO: find relationship
            *d-velocity:                          10%
                v = v-actual/v-goal
            *e-lane                               5%
                TODO: find relationship
            *h = a? + bx + c? + e?
        else
            *a-distance to car in front           50%
               TODO: find relationship
            *b-velocity: v-actual/v-goal          30%
                v = v-actual/v-goal
            *c-lane                               20%
               TODO: find relationship
            *h = a? + bv + c?
    */
}

foat transition()
{
    /*
     TODO: investigate average acceleration
    */
}

float traffic_simulation()
{

    /*while not_last_car
        *Call transition function to calculte new possible states
        *Call heuristic_function to select best new state
        *Update current state
    Setup for next iteration (traffic lights, pothele)
    */
}

int main (args, argv)
{

}