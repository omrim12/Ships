#ifndef EX3_BOATS_SIMULATION_CRUISERBOAT_H
#define EX3_BOATS_SIMULATION_CRUISERBOAT_H

#include <iostream>
#include <memory>
#include <string>

#include "Boat.h"

class freighterBoat;

class cruiserBoat : public Boat	{

private:
    const int MAX_SPEED = 75;
    const int attack_range;
//    bool to_attack;
//    weak_ptr<Boat> attack_boat;

public:
    //not implemented:
    //destination, dock at, stop
    cruiserBoat(string boat_name, int pow, int range): Boat(boat_name,0,pow), attack_range(range){};
    ~cruiserBoat();
    void course(double deg, double speed);
    void position(double x, double y, double speed);
    void attack(weak_ptr<Boat> boat);
    void in_move_status();

   // used for compilation purposes only
   void destination(weak_ptr<Port>,double);
   void patrol_move_to_first();
   void dock(weak_ptr<Port>);
   void in_dock_status();
   void refuel();
   void stop();




    friend ostream& operator<<(ostream& out, const cruiserBoat& ship);
};


#endif
