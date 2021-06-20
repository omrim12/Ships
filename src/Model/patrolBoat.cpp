#include "patrolBoat.h"

class cmp {
    //sort ports by distance from start port.
    //second parameter -> alphabet.
    Port start_port;
public:
    cmp(const Port &start) : start_port(start) {};

    bool operator()(weak_ptr<Port> p1, weak_ptr<Port> p2) {
        if (start_port.get_Location().distance_from(p1.lock()->get_Location()) ==
            start_port.get_Location().distance_from(p2.lock()->get_Location())) {
            return p1.getPortName() < p2.getPortName();
        }
        return start_port.get_Location().distance_from(p1.lock()->get_Location()) <
               start_port.get_Location().distance_from(p2.lock()->get_Location());
    }

};


void patrolBoat::start_patrol(const Port &start_Port) {

    std::sort(my_Ports.begin(), my_Ports.end(), cmp(start_Port));
    curr_port_name = start_Port.getPortName();

    /*
     * 2. set first destination
     * 3. define boat status
     */
}

ostream &operator<<(ostream &out, const patrolBoat &ship) {
    string status_str = "";
    switch(ship.generalStatus){
        case(Move):
            status_str += "Moving to " + ship.destPortName + " on course " + to_string(ship.direction.get_degree())  + " deg";
            break;

        case(Docked):
            status_str += "At port " + ship.curr_port_name;

            switch(ship.dockedStatus){
                case(fuel):
                    status_str += " now fueling"
                    break;
                case(docke):
                    status_str += " now docked"
                    break;
                case(set_dest):
                    status_str += "now setting next destination"
                    break;
            }
            break;

        case(Dead):
            status_str += "Dead in the water";
            break;

        case(Stopped):
            status_str += "Stopped";
            break;

        default:
            cerr << "WTFFFFF" << endl;
            break;

    }
    out << "Patrol_boat " << ship.getBoatName() << " at " << ship.curr_Location << ", fuel: " + ship.curr_fuel
        << " kl, resistance: " << ship.resistance << ", " << status_str <<", speed "<<ship.curr_speed <<" nm/hr"<<endl;

    return out;
}

//Patrol_boat Shikishima at (9.95, 1.00), fuel: 880.00 kl, resistance: 10, Moving to Nagoya
//on course 84.29 deg, speed 10.00 nm/hr