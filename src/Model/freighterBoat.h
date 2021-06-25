#ifndef EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
#define EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
#include "Boat.h"

class freighterBoat : public Boat  {
private:
    /*constants*/
    const int MAX_CONTAINERS_CAPACITY;
    static const int MAX_FRI_FUEL = 500000;
    const int MAX_SPEED = 40;
    const double FUEL_PER_NM = 1000;


public:
    /*c'tors & d'tors*/
    freighterBoat(string& boat_name,int cont_cap, int res);
    ~freighterBoat()	{}

    /*class functions*/
    void load_boat();
    void unload_boat();
    void course(int deg, double speed);

    void position(double x, double y, double speed);

    void destination(weak_ptr<Port> port, double speed);

    void dock(weak_ptr<Port> port);

    void attack(weak_ptr<Port> port);

    void refuel();

    void stop();

    void in_dock_status();
    void in_move_status();

    /*print operator*/
    friend ostream& operator<<(ostream& out, const freighterBoat& ship);
};


#endif
