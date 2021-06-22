#ifndef EX3_BoatS_SIMULATION_Boat_H
#define EX3_BoatS_SIMULATION_Boat_H

#include "Direction.h"
#include "gameObj.h"
#include "Port.h"

using namespace std;

enum Status {
    Stopped, Docked, Dead, Move
};
/*****************************************/
class freighterBoat;
class cruiserBoat;
class patrolBoat;
/*****************************************/

class Boat : public gameObj {
protected:
    /*data members*/

    const double MAX_BOAT_FUEL;
    const string name;
    int resistance;
    double curr_fuel;
    Status status;
    double curr_speed;
    Direction direction;
    Location curr_Location;
    Location dest_Location;
    int num_of_containers;
    bool waiting_for_fuel;

    /*data members update*/
    double new_speed;
    double add_fuel;
    Status new_status;
    Location new_dest_Location;
    Direction new_Direction;
    int new_num_of_containers;

public:
    Boat(string& boat_name,double fuel=0, int res=0, int num=0) :name(boat_name),MAX_BOAT_FUEL(fuel), resistance(res), curr_fuel(fuel), status(Stopped), curr_speed(0),
                                          direction(Direction()), curr_Location(Location()),
                                          dest_Location(Location()), new_speed(0), add_fuel(0), new_status(status),
                                          new_dest_Location(dest_Location), new_Direction(Direction()),
                                          new_num_of_containers(-1), num_of_containers(num),waiting_for_fuel(false) {};

    virtual ~Boat() {};

    Boat(const Boat &) = delete;

    Boat(Boat &&) = delete;

    Boat &operator=(const Boat &) = delete;

    Boat &operator=(Boat &&) = delete;

    virtual int getCurrSpeed() const { return curr_speed; }

    virtual void setCurrSpeed(int currSpeed) { curr_speed = currSpeed; }

    virtual const string &getBoatName() const { return name; }

    virtual Status getStatus() const { return status; }
    virtual const string &getName() const { return name; }
    virtual double getMaxFuel() const	{ return MAX_BOAT_FUEL; }

    virtual double getCurrFuel() const { return curr_fuel; }

    virtual int getResistance() { return resistance; }

    virtual void setResistance(int res) { resistance = res;}

    virtual void setToAddFuel(double fuel) { add_fuel = fuel; }

    virtual void setWaitingForFuel(bool b){waiting_for_fuel=b;}

    virtual void setNumOfContainers(int numOfContainers) { new_num_of_containers = numOfContainers; }

    virtual int getNumOfContainers() const { return num_of_containers; }

    virtual Boat& operator++(){
        resistance++;
        return *this;
    }

    virtual Boat& operator--(){
        resistance--;
        return *this;
    }

    virtual void executeByStatus(Status new_status) {

        switch (new_status) {
            case Stopped:
                new_speed = 0;
                stop();
                break;
            case Docked:
                new_speed = 0;
                dock();
                break;
            case Dead:
                new_speed = 0;
                dead();
                break;
            case Move:
                move();
                break;
        }

    }

    virtual const Location &getCurrLocation() const { return curr_Location; }

    virtual void setCurrLocation(const Location &currLocation) { curr_Location = currLocation; }

    virtual const Location &getDestLocation() const { return dest_Location; }

    virtual void setDestLocation(const Location &destLocation) {new_dest_Location=destLocation;}

    virtual const Direction &getDirection() const { return direction; }

    virtual void setDirection(const Direction &direction){ new_Direction = direction;}

    virtual void ask_fuel() = 0;

    virtual void stop() = 0;

    virtual void dock() = 0;

    virtual void dead() = 0;

    virtual void move() = 0;

    virtual string toString() const = 0;

    virtual void update() = 0;
};

#endif
