#include "patrolBoat.h"

/********************************************/
class cmp {
    //sort ports by distance from start port.
    //second parameter -> alphabet.
    Port start_port;
public:
    cmp(const Port &start) : start_port(start) {};

    bool operator()(weak_ptr<Port> p1, weak_ptr<Port> p2) {
        if (start_port.get_Location().distance_from(p1.lock()->get_Location()) ==
            start_port.get_Location().distance_from(p2.lock()->get_Location())) {
            return p1.lock()->getPortName() < p2.lock()->getPortName();
        }
        return start_port.get_Location().distance_from(p1.lock()->get_Location()) <
               start_port.get_Location().distance_from(p2.lock()->get_Location());
    }

};

/********************************************/
patrolBoat::~patrolBoat() {}

/********************************************/
patrolBoat::patrolBoat(string &boat_name, int res) : Boat(boat_name, MAX_PAT_FUEL, res), cursor(0),dockedStatus(fuel){
//    /TODO:*copy all ports vector to - my ports ****
}

/********************************************/
void patrolBoat::start_patrol(const Port &start_Port, double speed) {

    std::sort(my_dest_ports.begin(), my_dest_ports.end(), cmp(start_Port));
    cursor = 0;
    setDestLocation(my_dest_ports[cursot]);
    setCurrSpeed(speed);
    new_status = Move;
}

/********************************************/
ostream &operator<<(ostream &out, const patrolBoat &ship) {
    string status_str = "";
    switch (ship.status) {
        case (Move):
            status_str += "Moving to ";
            status_str += ship.dest_Location;
            status_str += " on course " + to_string(ship.direction.get_degree()) + " deg";
            break;

        case (Docked):
            status_str += "At port " + ship.curr_dest_name;

            switch (ship.dockedStatus) {
                case (fuel):
                    status_str += " now fueling";
                    break;
                case (dock):
                    status_str += " now docked";
                    break;
                case (set_dest):
                    status_str += "now setting next destination";
                    break;
            }
            break;

        case (Dead):
            status_str += "Dead in the water";
            break;

        case (Stopped):
            status_str += "Stopped";
            break;

        default:
            cerr << "WTFFFFF" << endl;
            break;

    }
    out << "Patrol_boat " << ship.name << " at " << ship.curr_Location << ", fuel: " << ship.curr_fuel
        << " kl, resistance: " << ship.resistance << ", " << status_str << ", speed " << ship.curr_speed << " nm/hr"
        << endl;

    return out;
}

/********************************************/
void patrolBoat::setDestLocation(const Location &dest_loc) {
    dest_Location = dest_loc;
    setDirection(Direction(dest_loc, curr_Location));
}

/********************************************/
void patrolBoat::ask_fuel() {
    //can fuel only if ready to fuel queue is empty
    Port curr_port = my_dest_ports[cursor];

    if (curr_port.readyToFuelEmpty()) {
        curr_port.fuel(this);
        curr_fuel += add_fuel;
        add_fuel = 0;
    }
    return;

}

/********************************************/
void patrolBoat::stop() {
    //clear all destinations
    while (new_patrols.size() > 0) {
        new_patrols.pop();
    }
    cursor = 0;
}

/********************************************/
void patrolBoat::dock() {
    switch (dockedStatus) {
        case fuel:
            ask_fuel();
            break;
        case dock:
            break;
        case set_dest:
            if (cursor == my_dest_ports.size() - 1) {
                if (new_patrols.empty()) {
                    cursor = 0;
                    dockedStatus = 0;
                    new_status = Stopped;
                } else {
                    start_patrol(new_patrols.front().second, new_patrols.front().first);
                    new_patrols.pop();
                }
                return;
            } else {
                cursor++
                setDestLocation(my_dest_ports[cursor]);
            }
    }
    dockedStatus = (dockedStatus + 1) % 3;
    if (dockedStatus == 0) {
        new_status = Move;
    }
}

/********************************************/
void patrolBoat::dead() {

}

/********************************************/
void patrolBoat::move() {
    if (curr_Location.distance_from(dest_Location) <= 0.1) {
        curr_Location = dest_Location;
        new_status = Docked;
    }
    Location next_Location = (new_status == Docked ? dest_Location : curr_Location.next_Location(direction,
                                                                                                 curr_speed));
    double use_fuel = curr_Location.distance_from(next_Location) * FUEL_PER_NM;

    if (curr_fuel - use_fuel < 0) {
        if (curr_Location != dest_Location) {
            new_status = Dead;
        }
    } else {
        curr_fuel -= use_fuel;
        curr_Location = next_Location;
    }
}

/********************************************/
void patrolBoat::update() {

    executeByStatus(status);

    status = new_status;
    curr_speed = new_speed;
    direction = new_Direction;
    dest_Location = new_dest_Location;
}
/********************************************/