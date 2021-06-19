#ifndef EX3_SHIPS_SIMULATION_PATROLBOAT_H
#define EX3_SHIPS_SIMULATION_PATROLBOAT_H
#include "Boat.h"
#include <vector>
#include "Port.h"
#include "cruiserBoat.h"


class patrolBoat : public Boat{
private:
    static const int MAX_PAT_FUEL = 900000;
    const int MAX_SPEED = 15;
    const int FUEL_PER_NM = 2000;
    int resistance;
    vector <unique_ptr<Port>> my_Ports;
public:
    patrolBoat(int res):Boat(MAX_PAT_FUEL),resistance(res),my_Ports(vector<unique_ptr<Port> >{})	{
    	curr_fuel = MAX_PAT_FUEL;
    	new_fuel = curr_fuel;
    }
    void start_journey(const Port& start_Port);
    bool operator <(const cruiserBoat& other) const;
    string toString() const;

};


#endif //EX3_SHIPS_SIMULATION_PATROLBOAT_H
