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
    Stopped, Docked, Dead, Move_to_Course, Move_to_Position, Move_to_Dest
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
    int resistance;
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
    Boat(string &boat_name, double max_fuel = 0, int res = 0, int num = 0) : name(boat_name), MAX_BOAT_FUEL(max_fuel),
                                                                             resistance(res), curr_fuel(max_fuel),
                                                                             status(Stopped), curr_speed(0),
                                                                             direction(Direction()),
                                                                             curr_Location(Location()),
                                                                             dest_Location(Location()), type(None),
                                                                             dest_port(weak_ptr<Port>()),
                                                                             available(true),
                                                                             waiting_in_fuel_queue(false),
                                                                             ask_fuel(false) {};

    virtual ~Boat() {};

    Boat(const Boat &) = delete;

    Boat(Boat &&) = delete;

    Boat &operator=(const Boat &) = delete;

    Boat &operator=(Boat &&) = delete;

    virtual void
    addOrder(const string &ord_str, int deg=0, double speed=0, double x=0, double y=0, weak_ptr<Port> port=weak_ptr<Port>(), weak_ptr<Boat> boat=weak_ptr<Boat>(),
             int cont_capacity=0) {
        order curr_ord;
        if (ord_str == "course") curr_ord = Course;
        else if (ord_str == "position") curr_ord = Position;
        else if (ord_str == "destination") curr_ord = Destination;
        else if (ord_str == "dock_at") curr_ord = Dock_at;
        else if (ord_str == "attack") curr_ord = Attack;
        else curr_ord = Stop;

        Order new_order = Order(curr_ord, deg, speed, port, boat, x, y, cont_capacity);
        orders_queue.push(new_order);   //adding order to queue
    }

    virtual bool dest_is_load(weak_ptr<Port> dest) {
        for (auto &p: ports_to_load) {
            if (p.lock().get() == dest.lock().get()) { ///???operator ==
                return true;
            }
        }
        return false;
    }

    virtual bool dest_is_unload(weak_ptr<Port> dest) {
        for (auto &p: ports_to_unload) {
            if (p.port.lock().get() == dest.lock().get()) { ///???operator ==
                return true;
            }
        }
        return false;
    }

    virtual void add_load_dest(weak_ptr<Port> load_port) {
        if (dest_is_load(load_port))return;  //there is nothing to do
        else if (dest_is_unload(load_port)) cerr << "Destination is already for unload." << endl;
        else ports_to_load.push_back(load_port);
    }

    virtual void add_unload_dest(weak_ptr<Port> unload_port, int capacity) {
        if (dest_is_unload(unload_port))return;  //there is nothing to do
        else if (dest_is_load(unload_port)) cerr << "Destination is already for load." << endl;
        else {
            unload_Port new_port(unload_port, capacity);
            ports_to_unload.push_back(new_port);
        }
    }

    virtual Boat &operator++() {
        resistance++;
        return *this;
    }

    virtual Boat &operator--() {
        resistance--;
        return *this;
    }

    virtual void course(int deg, double speed) = 0;

    virtual void position(double x, double y, double speed) = 0;

    virtual void destination(weak_ptr<Port> port, double speed) = 0;

    virtual void dock(weak_ptr<Port> port) = 0;

    virtual void attack(weak_ptr<Port> port) = 0;

    virtual void refuel() = 0;

    virtual void stop() = 0;

    virtual void setAvailable(bool b) { available = b; }

    virtual void addFuel(int cap) { curr_fuel += cap; }

    virtual void setWaiting(bool b) { waiting_in_fuel_queue = b; }

    virtual void setAskForFuel(bool b) {ask_fuel = b;}

    //*inside status functions*
    virtual void in_dock_status() = 0;

    virtual void in_move_status() = 0;


    virtual void update() {
        if (available) {
            if (!orders_queue.empty()) {
                //start actions for curr order
                Order curr_order = orders_queue.front();
                available = false; //not available for other orders

                switch (curr_order.ord) {
                    case (Course):
                        course(curr_order.deg, curr_order.speed);
                        break;
                    case (Position):
                        position(curr_order.x, curr_order.y, curr_order.speed);
                        break;
                    case (Destination):
                        destination(curr_order.port, curr_order.speed);
                        break;
                    case (Dock_at):
                        dock(curr_order.port);
                        break;
                    case (Attack):
                        attack(curr_order.port);
                        break;
                    case (Stop):
                        stop();
                        break;
                }
            }
            //remove order from queue
            orders_queue.pop();
        } else {
            switch (status) {
                case (Docked):
                    in_dock_status();
                    break;
                case (Move_to_Dest):
                    in_move_status();
                    break;
                case (Move_to_Course):
                    in_move_status();
                    break;
                case (Move_to_Position):
                    in_move_status();
                    break;
                case(Stopped):
                    available=true;
                    break;
                case (Dead):
                    //Boat stay in dead status forever
                    break;
            }
        }
    }
};

#endif
