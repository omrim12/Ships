#ifndef EX3_BoatS_SIMULATION_Boat_H
#define EX3_BoatS_SIMULATION_Boat_H

#include "Direction.h"
#include "gameObj.h"
#include "Port.h"
#include <queue>

using namespace std;

enum order {
    course, position, destination, load_at, unload_at, dick_at, attack, refuel, stop
};

enum Status {
    Stopped, Docked, Dead, Move
};

struct Order {
    order ord;
    int deg;
    double speed;
    int x;
    int y;
    string portName;
    string boatName;
    int num_of_containers;

    Order(order arg_ord, int arg_deg = 0, double arg_speed = 0, const string &port = "", const string &boat = "",
          int arg_x = 0, int arg_y = 0, int containers = 0) :
            ord(arg_ord), deg(arg_deg), speed(arg_speed), portName(port), boatName(boat), x(arg_x), y(arg_y),
            num_of_containers(containers){};

};

struct unload_Port{
    Port port;
    int capacity;
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

    queue<Order> orders_queue;

    vector<Port> ports_to_load;
    vector<unload_Port> ports_to_unload;


public:
    Boat(string &boat_name, double fuel = 0, int res = 0, int num = 0) : name(boat_name), MAX_BOAT_FUEL(fuel),
                                                                         resistance(res), curr_fuel(fuel),
                                                                         status(Stopped), curr_speed(0),
                                                                         direction(Direction()),
                                                                         curr_Location(Location()),
                                                                         dest_Location(Location()){};

    virtual ~Boat() {};

    Boat(const Boat &) = delete;

    Boat(Boat &&) = delete;

    Boat &operator=(const Boat &) = delete;

    Boat &operator=(Boat &&) = delete;

    virtual int getSpeed() const { return curr_speed; }

    virtual const string &getBoatName() const { return name; }

    virtual Status getStatus() const { return status; }

    virtual const string &getName() const { return name; }

    virtual double getMaxFuel() const { return MAX_BOAT_FUEL; }

    virtual double getCurrFuel() const { return curr_fuel; }

    virtual int getResistance() { return resistance; }

    virtual void setResistance(int res) { resistance = res; }

    virtual int getNumOfContainers() const { return num_of_containers; }

//    virtual void executeByStatus(Status new_status) {

    virtual const Location &getCurrLocation() const { return curr_Location; }

    virtual void setCurrLocation(const Location &currLocation) { curr_Location = currLocation; }

    virtual const Location &getDestLocation() const { return dest_Location; }

    virtual void setDestLocation(const Location &destLocation) { /*new_dest_Location = destLocation; */}

    virtual const Direction &getDirection() const { return direction; }

    virtual void setDirection(const Direction &direction) { /* direction = direction; */}

    virtual void setCourse(const double &deg) { /* new_Direction = Direction(deg); */}

    virtual Boat &operator++() {
        resistance++;
        return *this;
    }

    virtual Boat &operator--() {
        resistance--;
        return *this;
    }

    virtual void ask_fuel() = 0;

    virtual void stop() = 0;

    virtual void dock() = 0;

    virtual void dead() = 0;

    virtual void move() = 0;

    virtual string toString() const = 0;

    virtual void update() = 0;
};

#endif
