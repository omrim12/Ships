#ifndef EX3_BOATS_SIMULATION_CRUISERBOAT_H
#define EX3_BOATS_SIMULATION_CRUISERBOAT_H
#include "Boat.h"

class cruiserBoat : public Boat{
private:
    const int MAX_SPEED = 75;
    int attack_power;
    int attack_range;
public:
    void attack(Boat& attack_boat);
};


#endif //EX3_BOATS_SIMULATION_CRUISERBOAT_H
