#ifndef EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
#define EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
#include "Boat.h"

class freighterBoat : public Boat  {
private:
	/*constants*/
    const int MAX_CONTAINERS_CAPACITY;//TODO: initialize right value.
    static const int MAX_FRI_FUEL = 500000;
    const int MAX_SPEED = 40;
    const int FUEL_PER_NM = 1000;
    const int resistance;

    /*data members*/
    bool load_status;
    int num_of_containers;
    bool warning;

    /*data members update*/
    bool new_load_status;
    int new_num_of_containers;

public:
    /*c'tors & d'tors*/
    freighterBoat(int res, int cont_cap):Boat(),MAX_CONTAINERS_CAPACITY(cont_cap),resistance(res),curr_fuel(MAX_FRI_FUEL),load_status(0), num_of_containers(MAX_CONTAINERS_CAPACITY),
								warning(0),new_num_of_containers(num_of_containers), new_load_status(load_status){ curr_fuel = MAX_FRI_FUEL; new_fuel = curr_fuel; };
    ~freighterBoat()	{}

    /*getters & setters*/
    void setToLoad(bool b){new_load_status = b;}
    void setDestLocation(const Location &destLocation);
    void setDirection();
    void setPort(int speed, bool b, const Location& dest_loc);

    /*class functions*/
    void unload(int cont, unique_ptr<Port>& port);
    void load(unique_ptr<Port>& port);
    void fuel(unique_ptr<Port>& port);
    void stop();
    void dock();
    void dead();
    void move();
};


#endif //EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
