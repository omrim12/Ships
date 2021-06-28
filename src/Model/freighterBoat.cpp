#include "freighterBoat.h"
#include "Direction.h"
#include<bits/stdc++.h>

freighterBoat::freighterBoat(string boat_name, int containers_capacity, int res) : Boat(boat_name, MAX_FRI_FUEL, res,
                                                                                         containers_capacity),
                                                                                    MAX_CONTAINERS_CAPACITY(
                                                                                            containers_capacity),
                                                                                    curr_num_of_containers(0),
                                                                                    waiting_in_fuel_queue(false),
                                                                                    ask_fuel(false),type(None) {};

/*************************************/
void freighterBoat::setNumOfContainers(int n) { curr_num_of_containers = n; }

/********************************/
bool freighterBoat::dest_is_load(weak_ptr<Port> dest) {
    for (auto &p: ports_to_load) {
        if (*p.lock().get() == *dest.lock().get()) {
            return true;
        }
    }
    return false;
}

/********************************/
bool freighterBoat::dest_is_unload(weak_ptr<Port> dest) {
    for (auto &p: ports_to_unload) {
        if (*(p.port.lock().get()) == *(dest.lock().get())) {
            return true;
        }
    }
    return false;
}

/********************************/
void freighterBoat::add_load_dest(weak_ptr<Port> load_port) {
    if (dest_is_load(load_port))return;  //there is nothing to do
    else if (dest_is_unload(load_port)) cerr << "Destination is already for unload." << endl;
    else ports_to_load.push_back(load_port);
}

/********************************/
void freighterBoat::add_unload_dest(weak_ptr<Port> unload_port, int capacity) {
    if (dest_is_unload(unload_port))return;  //there is nothing to do
    else if (dest_is_load(unload_port)) cerr << "Destination is already for load." << endl;
    else {
        unload_Port new_port(unload_port, capacity);
        ports_to_unload.push_back(new_port);
    }
}

/********************************/
void freighterBoat::course(double deg, double speed) {
    status = Move_to_Course;
    direction = Direction(deg);
    curr_speed = speed;
    dest_port.reset();
    type = None;
}

/*************************************/
void freighterBoat::position(double x, double y, double speed) {
    status = Move_to_Position;
    direction = Direction(Location(x, y), curr_Location);
    curr_speed = speed;
    dest_port.reset();
    type = None;
}

/*************************************/
void freighterBoat::destination(weak_ptr<Port> port, double speed) {
    if (dest_is_load(port)) type = load;
    else if (dest_is_unload(port)) type = unload;
    else type = None;
    status = Move_to_Dest;
    direction = Direction(port.lock()->get_Location(), curr_Location);
    dest_port = std::move(port);
    curr_speed = speed;
}

/*************************************/
void freighterBoat::dock(weak_ptr<Port> port) {
    if (curr_Location.distance_from(port.lock()->get_Location()) <= 0.1) {
        curr_speed = 0;
        curr_Location = port.lock()->get_Location();
        if (status == Move_to_Dest) {
            if (*port.lock().get() == *dest_port.lock().get()) {
                //case of docking port is same as destination port:
                //*check if destination is from load/unload type
                switch (type) {
                    case (load):
                        load_boat();
                        break;
                    case (unload):
                        unload_boat();
                        break;
                    default:
                        break;
                }
            }
        }
        status = Docked;
        type = None;

    } else cerr << "WARNING" << port.lock()->getPortName() << " is too far for Docking. " << endl;
}

/*************************************/
void freighterBoat::refuel() {
    std::shared_ptr<Boat> me(this);
    dest_port.lock()->addToQueue(weak_ptr<Boat>(me));
    waiting_in_fuel_queue = true;
    ask_fuel = false;
    return;
}

/*************************************/
void freighterBoat::stop() {
    status = Stopped;
    curr_speed = 0;
    dest_port.reset();
    setAvailable(true); //available for other orders
}

/*************************************/
void freighterBoat::unload_boat() {
    int to_unload;
    for (auto &p: ports_to_unload) {
        if (*p.port.lock().get() == *dest_port.lock().get()) {
            to_unload = p.capacity;
            break;
        }
    }

    if (curr_num_of_containers < to_unload) {
        dest_port.lock()->load_port(curr_num_of_containers);
        curr_num_of_containers = 0;
        type = None;
        cerr << "WARNING: containers capacity at " << name << " boat is smaller then required to unload. " << endl;
        return;
    }
    //else
    dest_port.lock()->load_port(to_unload);
    curr_num_of_containers -= to_unload;
    ports_to_unload.erase(find(ports_to_unload.begin(), ports_to_unload.end(), dest_port));
    type = None;
}

/*************************************/

void freighterBoat::load_boat() {
    dest_port.lock()->unload_port(MAX_CONTAINERS_CAPACITY - curr_num_of_containers);
    curr_num_of_containers = MAX_CONTAINERS_CAPACITY;
    //delete port from load ports list
    ports_to_load.erase(find(ports_to_load.begin(), ports_to_load.end(), dest_port));
}

/*************************************/

void freighterBoat::in_dock_status() {
    if (ask_fuel) {
        refuel();
    }
}

/*************************************/
void freighterBoat::in_move_status() {
    if (curr_Location.distance_from(dest_Location) <= 0.1) {
        //case of boat already can dock at destination
        status = Docked;
        curr_speed = 0;
        curr_Location = dest_Location;
        return;
    }
    Location next_Location = curr_Location.next_Location(direction, curr_speed);
    double use_fuel = curr_Location.distance_from(next_Location) * FUEL_PER_NM;

    if (curr_fuel - use_fuel < 0) {
        if (curr_Location != dest_Location) {
            status = Dead;
            curr_speed = 0;
        }
    } else {
        curr_fuel -= use_fuel;
        curr_Location = next_Location;
    }
}

/*************************************/
void freighterBoat::setWaiting(bool b) { waiting_in_fuel_queue = b; }
/********************************/
void freighterBoat::setAskForFuel(bool b) { ask_fuel = b; }
/*************************************/
int freighterBoat::getMAXSpeed(){return MAX_SPEED;}
/*************************************/
ostream &operator<<(ostream &out, const freighterBoat &ship) {

    string stat_string = "";

    switch (ship.status) {
        case (Move_to_Dest):
            stat_string +=
                    "Moving to " + ship.dest_port.lock()->getPortName() + " on course " + to_string(ship.direction.get_degree()) +
                    " deg" + ", speed " + to_string(ship.curr_speed) + " nm/hr " + " Containers: " + to_string(ship.curr_num_of_containers);
            switch (ship.type) {
                case (load):
                    stat_string += "moving to loading destination. ";
                    break;
                case (unload):
                    stat_string += "moving to unloading destination. ";
                    break;
                case (None):
                    stat_string += "no cargo destinations. ";
                    break;
            }
            break;
        case (Move_to_Position):
            stat_string += "Moving to position " + string(ship.dest_Location) + ", speed " + to_string(ship.curr_speed) + " nm/hr " +
                           " Containers: " + to_string(ship.curr_num_of_containers);
            break;
        case (Move_to_Course):
            stat_string +=
                    "Moving on course " + to_string(ship.direction.get_degree()) + ", speed " + to_string(ship.curr_speed) + " nm/hr " +
                    " Containers: " + to_string(ship.curr_num_of_containers);
            break;
        case (Docked):
            stat_string += "Docked at " + ship.dest_port.lock()->getPortName();
            break;

        case (Dead):
            stat_string += "Dead in the water";
            break;

        case (Stopped):
            stat_string += "Stopped";
            break;

        default:
            cerr << "WTFFFFF" << endl;
            break;
    }

    stat_string += ", ";

    out << "Freighter " << ship.name << " at " << ship.curr_Location << ", fuel: " << ship.curr_fuel << ", res_pow: "
        << ship.res_pow << ", " << stat_string;

    return out;
}

/***************** USED FOR COMPILATION ONLY *******************/
void freighterBoat::patrol_move_to_first()	{}
/*************************************/
void freighterBoat::attack(weak_ptr<Boat>)	{}
/*************************************/
