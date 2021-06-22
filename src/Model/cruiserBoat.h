#ifndef EX3_BOATS_SIMULATION_CRUISERBOAT_H
#define EX3_BOATS_SIMULATION_CRUISERBOAT_H
#include "Boat.h"
#include<boost/pointer_cast.hpp>

class freighterBoat;

class cruiserBoat : public Boat	{

private:
    const int MAX_SPEED = 75;
    const int attack_power;
    const int attack_range;
    bool to_attack;
    weak_ptr<Boat> attack_boat;

public:
    cruiserBoat(string& boat_name): Boat(boat_name), to_attack(false){};
    ~cruiserBoat();
    void attackNextTick(shared_ptr<Boat>& boat);
    void attack_now();
    void update();

    friend ostream& operator<<(ostream& out, const cruiserBoat& ship);
};


#endif
