#ifndef EX3_SHIPS_SIMULATION_PATROLBOAT_H
#define EX3_SHIPS_SIMULATION_PATROLBOAT_H
#include "Boat.h"
#include <vector>
#include "Port.h"
#include "Model.h"
#include "cruiserBoat.h"

class Model;

enum at_port_status {fuel,dock,set_dest};


class patrolBoat : public Boat{
private:
    static const int MAX_PAT_FUEL = 900000;
    const int MAX_SPEED = 15;
    const int FUEL_PER_NM = 2000;
    int const resistance;
    string curr_port_name;
    Status generalStatus;
    Docked_status dockedStatus;
    vector <weak_ptr<Port>> my_Ports;
    queue <weak_ptr<Port>> new_patrols;

public:
    patrolBoat(int res):Boat(MAX_PAT_FUEL),resistance(res),my_Ports(vector<weak_ptr<Port>>(Model::getInstance().getAllPorts()))	{
        ///*copy all ports vector to - my ports ****
    }
    void start_patrol(const Port& start_Port);
    bool operator <(const cruiserBoat& other) const;

    friend ostream& operator<<(ostream& out, const patrolBoat& ship);
};


#endif
