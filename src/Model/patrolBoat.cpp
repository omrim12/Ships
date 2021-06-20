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
patrolBoat::patrolBoat(int res):Boat(MAX_PAT_FUEL),resistance(res),curr_port_name(""),dockedStatus(set_dest),
								my_Ports(), new_patrols(queue<weak_ptr<Port> >{})	{
        ///*copy all ports vector to - my ports ****
    }
/********************************************/
void patrolBoat::start_patrol(const Port &start_Port) {

    std::sort(my_Ports.begin(), my_Ports.end(), cmp(start_Port));
    curr_port_name = start_Port.getPortName();

    /*
     * 2. set first destination
     * 3. define boat status
     */
}
/********************************************/
ostream &operator<<(ostream &out, const patrolBoat &ship) {
    string status_str = "";
    switch(ship.status){
        case(Move):
            status_str += "Moving to ";
        	status_str += ship.dest_Location;
        	status_str += " on course " + to_string(ship.direction.get_degree())  + " deg";
            break;

        case(Docked):
            status_str += "At port " + ship.curr_port_name;

            switch(ship.dockedStatus){
                case(fuel):
                    status_str += " now fueling";
                    break;
                case(dock):
                    status_str += " now docked";
                    break;
                case(set_dest):
                    status_str += "now setting next destination";
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
    out << "Patrol_boat " << ship.name << " at " << ship.curr_Location << ", fuel: " << ship.curr_fuel
        << " kl, resistance: " << ship.resistance << ", " << status_str << ", speed "<< ship.curr_speed <<" nm/hr" << endl;

    return out;
}
/********************************************/
void patrolBoat::stop()	{

}
/********************************************/
void patrolBoat::dock()	{

}
/********************************************/
void patrolBoat::dead()	{

}
/********************************************/
void patrolBoat::move()	{

}
/********************************************/
void patrolBoat::update()	{

	/*
	 *
	 * TODO: update by following steps:
	 *
	 *
	 *
	 *
	 *
	 *
	 *
	 *
	 *
	 *
	 *
	 */


}
/********************************************/
