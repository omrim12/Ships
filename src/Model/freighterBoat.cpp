#include "freighterBoat.h"

freighterBoat::freighterBoat(string& boat_name,int cont_cap, int res):Boat(boat_name,MAX_FRI_FUEL, res, cont_cap),MAX_CONTAINERS_CAPACITY(cont_cap),load_status(0),
                                     warning(0), new_load_status(load_status),to_unload(0) {};

/*************************************/
void freighterBoat::stop()	{
    dest_port.reset();
	new_dest_Location = curr_Location;
}

/*************************************/
void freighterBoat::dock()	{
    load_status ? load() : unload(to_unload);

    if(!waiting_for_fuel && (curr_fuel!=MAX_FRI_FUEL)){
        ask_fuel();
        waiting_for_fuel=true;
    }
}
/*************************************/

void freighterBoat::dead()	{}
/*************************************/
void freighterBoat::move()	{

	if(curr_Location.distance_from(dest_Location) <= 0.1)	{
	    new_status = Docked;

	}

	Location next_Location = (new_status == Docked ? dest_Location : curr_Location.next_Location(direction, curr_speed));
	double use_fuel = curr_Location.distance_from(next_Location) * FUEL_PER_NM;

	if(curr_fuel - use_fuel <= 0)	{
		if(curr_Location != dest_Location)	{
			new_status = Dead;
		}
	}

	else	{
		curr_fuel -= use_fuel;
		curr_Location = next_Location;
	}

}
/*************************************/
void freighterBoat::setDestLocation(const Location &destLocation){
    new_dest_Location = destLocation;
}
/*************************************/
void freighterBoat::setDirection()	{
	new_Direction = Direction(dest_Location,curr_Location);
	new_Direction.normalize();
}
/*************************************/
void freighterBoat::setPort(std::shared_ptr<Port>& port, int speed, bool b, const Location& dest_loc){
    new_status = Move;
    new_speed = speed;
    setDestLocation(dest_loc);
    setToLoad(b);
    setDirection();
    this->new_dest_port = port;

}
/*************************************/

void freighterBoat::setToLoad(bool b)	{new_load_status = b;}
/*************************************/
void freighterBoat::setToUnload(int capacity) { to_unload=capacity;}
/*************************************/
void freighterBoat::unload( ){

    if(new_num_of_containers < to_unload)	{

        dest_port.lock()->load(new_num_of_containers);
        new_num_of_containers = 0;
        to_unload=0;
        warning = 1;

        return;
    }

    dest_port.lock()->load(to_unload);
    new_num_of_containers -= to_unload;
    to_unload=0;
}
/*************************************/

void freighterBoat::load() {
    dest_port.lock()->unload(MAX_CONTAINERS_CAPACITY-new_num_of_containers);
    new_num_of_containers = MAX_CONTAINERS_CAPACITY;

}
/*************************************/
void freighterBoat::ask_fuel()	{

    std::shared_ptr<Boat> me(this);
    dest_port.lock()->addToQueue(weak_ptr<Boat>(me));
    return;

}
/*************************************/

void freighterBoat::update()	{

    if(waiting_for_fuel && new_status==Move ){
        waiting_for_fuel = false;
        dest_port.lock()->removeFromQueue(weak_ptr<Boat>(this));
    }

	executeByStatus(status);

	if( warning )	{ cerr << "WARNING: requested containers to unload capacity is greater than existing capacity." << endl; }

	warning = false;
	if(add_fuel > 0){
        curr_fuel += add_fuel;
        add_fuel=0;
        waiting_for_fuel=false;
	}
	status = new_status;
	curr_speed = new_speed;
    dest_port = new_dest_port;
	direction = new_Direction;
	load_status = new_load_status;
	dest_Location = new_dest_Location;
	num_of_containers = new_num_of_containers;
}
/*************************************/
ostream& operator<<(ostream& out, const freighterBoat& ship)	{

	string stat_string = "";

	switch(ship.status)	{
		case(Move):
			stat_string += "Moving to " + ship.destPortName + " on course " + to_string(ship.direction.get_degree())  + " deg";
			break;

		case(Docked):
			stat_string += "Docked at " + ship.destPortName;
			break;

		case(Dead):
			stat_string += "Dead in the water";
			break;

		case(Stopped):
			stat_string += "Stopped";
			break;

		default:
			cerr << "WTFFFFF" << endl;
			break;
	}

	stat_string += ", ";

	out << "Freighter " << ship.name << " at " << ship.curr_Location << ", fuel: " << ship.curr_fuel << ", resistance: " <<
			ship.resistance << ", " << stat_string << "speed " << ship.curr_speed << " nm/hr, Containers: " << ship.num_of_containers <<
			", moving to " << (ship.load_status ? "loading" : "unloading") << " destination" << endl;

	return out;
}

/*************************************/