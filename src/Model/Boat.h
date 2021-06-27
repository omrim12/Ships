#ifndef EX3_BoatS_SIMULATION_Boat_H
#define EX3_BoatS_SIMULATION_Boat_H

#include "Direction.h"
#include "gameObj.h"
#include "Port.h"
#include <queue>

using namespace std;

enum order {
    Course, Position, Destination, Dock_at, Attack, Stop
};
/*****************************************/
enum Status {
    Stopped, Docked, Dead, Move_to_Course, Move_to_Position, Move_to_Dest, Move_to_first
};

/*****************************************/
struct Order {
    order ord;
    int deg;
    double speed;
    double x;
    double y;
    weak_ptr<Port> port;
    weak_ptr<Boat> boat;
    int curr_num_of_containers;

    Order(order arg_ord, int arg_deg, double arg_speed, weak_ptr<Port> p, weak_ptr<Boat> b,
          double arg_x, double arg_y, int containers) :
            ord(arg_ord), deg(arg_deg), speed(arg_speed), x(arg_x), y(arg_y),
            curr_num_of_containers(containers) {
        port = std::move(p);
        boat = std::move(b);
    };

};

/*****************************************/
struct unload_Port {
    weak_ptr<Port> port;
    int capacity;

    unload_Port(weak_ptr<Port> p, int cap) : capacity(cap) {
        port = std::move(p);
    }

};

/*****************************************/
enum dest_type {
    load, unload, None
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
    int res_pow;         //resistance or attack power
    double curr_fuel;
    Status status;
    double curr_speed;
    Direction direction;
    Location curr_Location;
    Location dest_Location;
    std::weak_ptr<Port> dest_port;
    dest_type type;
    int curr_num_of_containers;
    bool available;
    bool waiting_in_fuel_queue;
    bool ask_fuel;

    queue<Order> orders_queue;

    vector<weak_ptr<Port>> ports_to_load;
    vector<unload_Port> ports_to_unload;


public:
    Boat(string &boat_name, double max_fuel = 0, int resPow = 0, int num = 0) :	MAX_BOAT_FUEL(max_fuel),
																	name(boat_name),
																	res_pow(resPow),
																	curr_fuel(max_fuel),
																	status(Stopped),
																	curr_speed(0),
																	direction(Direction()),
																	curr_Location(Location()),
																	dest_Location(Location()),
																	dest_port(weak_ptr<Port>()),
																	type(None),
																	curr_num_of_containers(0),
																	available(true),
																	waiting_in_fuel_queue(false),
																	ask_fuel(false) {};

    virtual ~Boat() {};

    Boat(const Boat &) = delete;

    Boat(Boat &&) = delete;

    Boat &operator=(const Boat &) = delete;

    Boat &operator=(Boat &&) = delete;

    Location getCurrLocation();

    string getName() const;

    void setNumOfContainers(int n);

    void setAvailable(bool b);

    void addFuel(int cap);

    void setWaiting(bool b);

    void setAskForFuel(bool b);

    void addOrder(const string &ord_str, int deg = 0, double speed = 0, double x = 0, double y = 0,
             weak_ptr<Port> port = weak_ptr<Port>(), weak_ptr<Boat> boat = weak_ptr<Boat>(),
             int cont_capacity = 0);

    virtual bool dest_is_load(weak_ptr<Port> dest);

    virtual bool dest_is_unload(weak_ptr<Port> dest);

    virtual void add_load_dest(weak_ptr<Port> load_port);

    virtual void add_unload_dest(weak_ptr<Port> unload_port, int capacity);

    virtual Boat &operator++();

    virtual Boat &operator--();

    virtual void course(int deg, double speed) = 0;

    virtual void position(double x, double y, double speed) = 0;

    virtual void destination(weak_ptr<Port> port, double speed) = 0;

    virtual void dock(weak_ptr<Port> port) = 0;

    virtual void attack(weak_ptr<Boat> boat) = 0;

    virtual void refuel() = 0;

    virtual void stop() = 0;

    //*inside status functions*
    virtual void in_dock_status() = 0;

    virtual void in_move_status() = 0;

    virtual void patrol_move_to_first() =0;

    virtual bool operator>(const Boat &other) const;

    virtual void update();
};

#endif
