#ifndef EX3_SHIPS_SIMULATION_PATROLBOAT_H
#define EX3_SHIPS_SIMULATION_PATROLBOAT_H

#include "Boat.h"
#include "cruiserBoat.h"

/********************************/
class Model;

/********************************/
enum at_port_status {
    fuel, dock, set_dest
};

/********************************/
class patrolBoat : public Boat {
private:
    int cursor;
    static const int MAX_PAT_FUEL = 900000;
    const int MAX_SPEED = 15;
    const int FUEL_PER_NM = 2000;
    at_port_status dockedStatus;
    vector<weak_ptr<Port>> my_dest_ports;
    queue <pair<double, weak_ptr<Port>>> new_patrols;       // <speed, start port>

public:
    /*c'tors & d'tors*/
    ~patrolBoat();

    patrolBoat(string& boat_name,int res);

    /*operators*/
    friend ostream &operator<<(ostream &out, const patrolBoat &ship);

    /*class functions*/
    void start_patrol(const Port &start_Port, double speed);

    bool operator<(const cruiserBoat &other) const;

    void setDestLocation(const Location &dest_loc);

    void stop();

    void dock();

    void dead();

    void move();

    void update();
    void ask_fuel();
};
/********************************/
#endif