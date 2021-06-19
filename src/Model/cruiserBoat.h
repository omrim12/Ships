#ifndef EX3_BOATS_SIMULATION_CRUISERBOAT_H
#define EX3_BOATS_SIMULATION_CRUISERBOAT_H
#include "Boat.h"

class cruiserBoat : public Boat	{

private:
    const int MAX_SPEED = 75;
    const int attack_power;
    const int attack_range;

public:
    cruiserBoat();
    ~cruiserBoat();

    void attack(Boat& attack_boat);
};


#endif
