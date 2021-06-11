#ifndef EX3_SHIPS_SIMULATION_PATROLBOAT_H
#define EX3_SHIPS_SIMULATION_PATROLBOAT_H
#include "Boat.h"
#include <vector>
#include "Port.h"
#include "cruiserBoat.h"


class patrolBoat : public Boat{
private:
    const int MAX_FUEL = 900000;
    const int MAX_SPEED = 15;
    const int FUEL_PER_NM = 2000;
    int resistance;
    vector <unique_ptr<Port>> my_Ports;
public:
    patrolBoat();
    void start_journey(const Port& start_Port);
    bool operator <(const cruiserBoat& other) const;
    string toString() const;

};


#endif //EX3_SHIPS_SIMULATION_PATROLBOAT_H
