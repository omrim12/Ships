#include "freighterBoat.h"

void freighterBoat::stop()	{
	new_destPortName = "";
	new_dest_Location = curr_Location;
}

void freighterBoat::dock()	{ curr_fuel += add_fuel; }

void freighterBoat::dead()	{}

void freighterBoat::move()	{

	if(curr_Location.distance_from(dest_Location) <= 0.1)	{ new_status = Docked; }

	Location next_Location = (new_status == Docked ? dest_Location : curr_Location.next_Location(direction, curr_speed));
	double use_fuel = curr_Location.distance_from(next_Location) * FUEL_PER_NM;

	if(curr_fuel - use_fuel <= 0)	{
		if(curr_Location != dest_Location)	{
			new_speed = 0;
			new_status = Dead;
		}
	}

	else	{
		curr_fuel -= use_fuel;
		curr_Location = next_Location;
	}

}

void freighterBoat::setDestLocation(const Location &destLocation){
    new_dest_Location = destLocation;
}

void freighterBoat::setDirection()	{
	new_Direction = Direction(dest_Location,curr_Location);
	new_Direction.normalize();
}

void freighterBoat::setPort(string destPortName, int speed, bool b, const Location& dest_loc){
    new_status = Move;
    new_speed = speed;
    setDestLocation(dest_loc);
    setToLoad(b);
    setDirection();
    this->new_destPortName = destPortName;

}

void freighterBoat::setToLoad(bool b)	{new_load_status = b;}

void freighterBoat::unload(int containers, unique_ptr<Port>& port){

	if( new_status == Docked ){

		if(new_num_of_containers < containers){

        	port->load(new_num_of_containers);
            new_num_of_containers = 0;
            warning = 1;
        }

        else{
            port->load(containers);
            new_num_of_containers -= containers;
        }

        return;
    }
}

void freighterBoat::load(unique_ptr<Port>& port) {
    port->unload(MAX_CONTAINERS_CAPACITY-new_num_of_containers);
    new_num_of_containers = MAX_CONTAINERS_CAPACITY;

}

void freighterBoat::fuel(unique_ptr<Port>& port)	{

	if( new_status == Docked )	{
	    std::unique_ptr<Boat> me(this);
	    port->addToQueue(me);
	    return;
	}

	 // exception if code reaches here
}

void freighterBoat::update()	{

	executeByStatus(status);

	if( warning )	{ cerr << "WARNING: requested containers to unload capacity is greater than existing capacity." << endl; }

	warning = false;
	status = new_status;
	curr_speed = new_speed;
	direction = new_Direction;
	load_status = new_load_status;
	destPortName = new_destPortName;
	dest_Location = new_dest_Location;
	num_of_containers = new_num_of_containers;
}

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
			", moving to " << (ship.load_status ? "loading" : "unloading") << " destination";

	return out;
}

