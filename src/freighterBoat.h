#ifndef EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
#define EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
#include "Boat.h"

class freighterBoat : public Boat  {
private:
	/*constants*/
    const int MAX_CONTAINERS_CAPACITY = 2020202;//TODO: initialize right value.
    const int MAX_FUEL = 500000;
    const int MAX_SPEED = 40;
    const int FUEL_PER_NM = 1000;
    const int resistance;

    /*data members*/
    int curr_fuel;
    bool load_status;
    int num_of_containers;
    bool warning;

    /*data members update*/
    int new_num_of_containers;
    bool new_load_status;

public:
    /*c'tors & d'tors*/
    freighterBoat(int res):Boat(),resistance(res),curr_fuel(MAX_FUEL),load_status(0), num_of_containers(MAX_CONTAINERS_CAPACITY),
								warning(0),new_num_of_containers(num_of_containers), new_load_status(load_status){};
    ~freighterBoat()	{}

    /*getters & setters*/
    void setToLoad(bool b){new_load_status = b;}
    void setDestLocation(const Location &destLocation);
    void setDirection();
    void setPort(int speed, bool b, const Location& dest_loc);

    /*class functions*/
    void unload(int cont, unique_ptr<Port>& port);
    void load(unique_ptr<Port>& port);
    void fuel(int);
    void stop();
    void dock();
    void dead();
    void move();
};


#endif //EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
