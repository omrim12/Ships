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

    /*data members*/
    std::weak_ptr<Port> dest_port;
    bool load_status;
    bool warning;

    /*data members update*/
    std::weak_ptr<Port> new_dest_port;
    bool new_load_status;


public:
    /*c'tors & d'tors*/
    freighterBoat(int cont_cap, int res);
    ~freighterBoat()	{}

    /*getters & setters*/
    void setDirection();
    void setToLoad(bool b);
    void setDestLocation(const Location &destLocation);
    void setPort(std::shared_ptr<Port>& port, int speed, bool b, const Location& dest_loc);

    /*class functions*/
    void unload(int cont);
    void ask_fuel();
    void update();
    void stop();
    void dock();
    void dead();
    void move();
    void load();

    /*print operator*/
    friend ostream& operator<<(ostream& out, const freighterBoat& ship);
};


#endif
