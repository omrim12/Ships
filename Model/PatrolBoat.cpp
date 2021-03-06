#include "PatrolBoat.h"
#include "Model.h"
#include "Location.h"
#include "Port.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>
/********************************************/
class cmp
{
	//sort ports by distance from start port.
	//second parameter -> alphabet.
	Port start_port;

public:
	cmp(const Port &start) : start_port(start){};

	bool operator()(weak_ptr<Port> p1, weak_ptr<Port> p2)
	{
		if (start_port.get_Location().distance_from(p1.lock()->get_Location()) ==
			start_port.get_Location().distance_from(p2.lock()->get_Location()))
		{
			return p1.lock()->getPortName() < p2.lock()->getPortName();
		}
		return start_port.get_Location().distance_from(p1.lock()->get_Location()) <
			   start_port.get_Location().distance_from(p2.lock()->get_Location());
	}
};

/********************************************/
PatrolBoat::~PatrolBoat() {}

/********************************************/
PatrolBoat::PatrolBoat(string boat_name, int res) : Boat(boat_name, MAX_PAT_FUEL, res), cursor(0), patrol_speed(0),
													dockedStatus(fuel)
{
	for (auto &port : Model::getInstance()->getAllPorts())
	{
		curr_patrol.push_back(weak_ptr<Port>(port));
	}
}

/********************************************/
void PatrolBoat::destination(weak_ptr<Port> port, double speed)
{
	start_patrol(port, speed);
}

/********************************************/
void PatrolBoat::start_patrol(weak_ptr<Port> port, double speed)
{

	std::sort(curr_patrol.begin(), curr_patrol.end(), cmp(*port.lock()));
	cursor = 0;
	dest_port = curr_patrol[cursor + 1];
	dest_Location = dest_port.lock()->get_Location();
	status = Move_to_Dest;
	curr_speed = speed;
	patrol_speed = speed;
}

/********************************************/
void PatrolBoat::stop()
{
	//clear all destinations
	while (orders_queue.size() > 0)
	{
		orders_queue.pop();
	}
	///is that true?????
	cursor = 0;
	curr_speed = 0;
	setAvailable(true);
}

/********************************************/
void PatrolBoat::in_dock_status()
{
	switch (dockedStatus)
	{
	case fuel:
		refuel();
		dockedStatus = _dock;
		break;
	case _dock:
		dockedStatus = set_dest;
		break;
	case set_dest:
		if ((unsigned int)cursor == curr_patrol.size() - 1)
		{
			//curr location is the last destination in curr patrol
			//return to first destination
			cursor = 0;
			dest_port = curr_patrol[cursor];
			dest_Location = dest_port.lock()->get_Location();
			status = Move_to_first;
			curr_speed = patrol_speed;
			return;
		}
		else
		{
			cursor++;
			dest_port = curr_patrol[cursor];
			dest_Location = dest_port.lock()->get_Location();
			status = Move_to_Dest;
			curr_speed = patrol_speed;
		}
		dockedStatus = fuel;
		break;
	}
}
/********************************************/
void PatrolBoat::patrol_move_to_first()
{
	if (curr_Location.distance_from(dest_Location) <= 0.1)
	{
		curr_Location = dest_Location;
		status = Docked;
		curr_speed = 0;
		setAvailable(true);
		cout << "END OF " << name << "'s PATROL. " << endl;
		return;
	}
	Location next_Location = curr_Location.next_Location(direction, curr_speed);
	double use_fuel = curr_Location.distance_from(next_Location) * FUEL_PER_NM;

	if (curr_fuel - use_fuel < 0)
	{
		status = Dead;
		curr_speed = 0;
	}
	else
	{
		curr_fuel -= use_fuel;
		curr_Location = next_Location;
	}
}

/********************************************/
int PatrolBoat::getMAXSpeed() { return MAX_SPEED; }
/********************************************/
void PatrolBoat::refuel()
{
	//can fuel only if ready to fuel queue is empty
	Port curr_port = *curr_patrol[cursor].lock();

	if (curr_port.readyToFuelEmpty())
	{
		curr_port.fuel(*this);
	}
	return;
}

/********************************************/
void PatrolBoat::in_move_status()
{
	if (curr_Location.distance_from(dest_Location) <= 0.1)
	{
		curr_Location = dest_Location;
		status = Docked;
		curr_speed = 0;
		return;
	}
	Location next_Location = curr_Location.next_Location(direction, curr_speed);
	double use_fuel = curr_Location.distance_from(next_Location) * FUEL_PER_NM;

	if (curr_fuel - use_fuel < 0)
	{
		status = Dead;
		curr_speed = 0;
	}
	else
	{
		curr_fuel -= use_fuel;
		curr_Location = next_Location;
	}
}

/********************************************/
ostream &operator<<(ostream &out, const PatrolBoat &ship)
{
	string status_str = "";
	switch (ship.status)
	{
	case (Move_to_Dest):
		status_str += "Moving to ";
		status_str += ship.dest_Location;
		status_str += " on course " + to_string(ship.direction.get_degree()) + " deg, ";
		status_str += "speed " + to_string(ship.curr_speed) + " nm/hr";
		break;

	case (Docked):
		status_str += "Docked at " + ship.dest_port.lock()->getPortName() + ", step time ";

		switch (ship.dockedStatus)
		{
		case (fuel):
			status_str += "1: Try to fuel. ";
			break;
		case (_dock):
			status_str += "2: Docking. ";
			break;
		case (set_dest):
			status_str += "3: Setting next destination in current patrol. ";
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
		<< " kl, res_pow: " << ship.res_pow << ", " << status_str << endl;

	return out;
}

/******************** FOR COMPILER PURPOSES ONLY ************************/
void PatrolBoat::attack(weak_ptr<Boat>) {}
/********************************************/
void PatrolBoat::course(double, double) {}
/********************************************/
void PatrolBoat::dock(weak_ptr<Port>) {}
/********************************************/
void PatrolBoat::position(double, double, double) {}
/********************************************/
void PatrolBoat::setAskForFuel(bool) {}
/********************************/
void PatrolBoat::setWaiting(bool) {}
/********************************/
