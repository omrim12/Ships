#ifndef EX3_SHIPS_SIMULATION_PATROLBOAT_H
#define EX3_SHIPS_SIMULATION_PATROLBOAT_H

#include "Boat.h"
#include "cruiserBoat.h"

/********************************/
class Model;

/********************************/
enum at_port_status {
    fuel, _dock, set_dest
};

/********************************/
class patrolBoat : public Boat {
private:
    int cursor;
    int patrol_speed;
    static const int MAX_PAT_FUEL = 900000;
    const int MAX_SPEED = 15;
    const int FUEL_PER_NM = 2000;
    at_port_status dockedStatus;
    vector<weak_ptr<Port>> curr_patrol;

public:
    /*c'tors & d'tors*/
    ~patrolBoat();

    patrolBoat(string boat_name, int res);

    void destination(weak_ptr<Port> port, double speed);

    void start_patrol(weak_ptr<Port> port, double speed);

    void stop();

    void refuel();

    void in_move_status();

    void in_dock_status();

    void patrol_move_to_first();

    void attack(weak_ptr<Boat>);

    void course(double,double);

    void dock(weak_ptr<Port>);

    void position(double,double,double);

    void setAskForFuel(bool);

    void setWaiting(bool);

    int getMAXSpeed();

    /*operators*/
    friend ostream &operator<<(ostream &out, const patrolBoat &ship);

};
/********************************/
#endif
