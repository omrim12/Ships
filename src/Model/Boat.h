#ifndef EX3_BoatS_SIMULATION_Boat_H
#define EX3_BoatS_SIMULATION_Boat_H
#include "Direction.h"
#include "gameObj.h"
#include "Port.h"

using namespace std;

enum Status {
    Stopped, Docked, Dead, Move
};

class Boat : public gameObj {
protected:
	/*data members*/
	string name;
	int curr_fuel;
	Status status;
	int curr_speed;
	Direction direction;
    Location curr_Location;
    Location dest_Location;

    /*data members update*/
    int new_speed;
    int new_fuel;
    Status new_status;
    Location new_curr_Location;
    Location new_dest_Location;
    Direction new_Direction;

public:
    Boat() : name(""),curr_fuel(0), status(Stopped), curr_speed(0), direction(Direction()), curr_Location(Location()),
			 dest_Location(Location()),  new_speed(0),
			 new_fuel(curr_fuel),new_status(status),new_curr_Location(curr_Location),
			 new_dest_Location(dest_Location), new_Direction(Direction()){};

    virtual ~Boat() = 0;

    Boat(const Boat&) = delete;
    Boat(Boat&&) = delete;
    Boat& operator=(const Boat&) = delete;
    Boat& operator=(Boat&&) = delete;

    virtual int getCurrSpeed() const { return curr_speed; }

    virtual void setCurrSpeed(int currSpeed) { curr_speed = currSpeed; }

    virtual const string &getName() const { return name; }

    virtual void setName(const string &name) { Boat::name = name; }

    virtual Status getStatus() const { return status; }

    virtual int getFuel() const	{ return curr_fuel; }

    virtual void setFuel(int fuel) { new_fuel = fuel; }

    virtual void setStatus(Status new_status) {
        switch (new_status) {
            case Stopped:
                curr_speed = 0;
                dest_Location = curr_Location;
                status = Stopped;
                stop();
                break;
            case Docked:
                status = Docked;
                dock();
                break;
            case Dead:
                status = Dead;
                dead();
                break;
            case Move:
                status = Move;
                move();
                break;
        }
    }

    virtual const Location &getCurrLocation() const { return curr_Location; }

    virtual void setCurrLocation(const Location &currLocation) { curr_Location = currLocation; }

    virtual const Location &getDestLocation() const { return dest_Location; }

    virtual void setDestLocation(const Location &destLocation) = 0;

    virtual const Direction &getDirection() const { return direction; }

    virtual void setDirection(const Direction &Direction) = 0;

    virtual void stop() = 0;
    virtual void dock() = 0;
    virtual void dead() = 0;
    virtual void move() = 0;

    virtual string toString() const = 0;

    virtual void update() override;
};

Boat::~Boat()	{}

#endif
