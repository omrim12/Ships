#include <string>
#include "Boat.h"
#include "PatrolBoat.h"
#include "CruiserBoat.h"
#include "FreighterBoat.h"
#include "Model.h"
using namespace std;

Boat::Boat(string &boat_name, double max_fuel, int resPow, int num) : MAX_BOAT_FUEL(max_fuel),
																	  name(boat_name),
																	  res_pow(resPow),
																	  curr_fuel(max_fuel),
																	  status(Stopped),
																	  curr_speed(0),
																	  direction(Direction()),
																	  curr_Location(Location()),
																	  dest_Location(Location()),
																	  dest_port(weak_ptr<Port>()),
																	  available(true) {}
shared_ptr<Boat> Boat::createBoat(const string &boat_name, const string &boat_type, int x, int y, int res_pow, int cap_range)
{

	if (boat_type == "Freighter")
	{
		shared_ptr<Boat> new_boat(new FreighterBoat(boat_name, cap_range, res_pow));
		return new_boat;
	}
	else if (boat_type == "Cruiser")
	{
		shared_ptr<Boat> new_boat(new CruiserBoat(boat_name, res_pow, cap_range));
		return new_boat;
	}
	else
	{
		shared_ptr<Boat> new_boat(new PatrolBoat(boat_name, res_pow));
		return new_boat;
	}
}
/********************************/
Location Boat::getCurrLocation() { return curr_Location; }
/********************************/
string Boat::getName() const { return name; }
/********************************/
double Boat::getFuel() const { return curr_fuel; }
/********************************/
double Boat::getMaxFuel() const { return MAX_BOAT_FUEL; }
/********************************/
void Boat::setAvailable(bool b) { available = b; }
/********************************/
void Boat::addFuel(int cap) { curr_fuel += cap; }
/********************************/
void Boat::addOrder(const string &ord_str, int deg, double speed, double x, double y, weak_ptr<Port> port, weak_ptr<Boat> boat,
					int containers_capacityacity)
{
	order curr_ord;
	if (ord_str == "course")
		curr_ord = Course;
	else if (ord_str == "position")
		curr_ord = Position;
	else if (ord_str == "destination")
		curr_ord = Destination;
	else if (ord_str == "dock_at")
		curr_ord = Dock_at;
	else if (ord_str == "attack")
		curr_ord = Attack;
	else
		curr_ord = Stop;

	Order new_order = Order(curr_ord, deg, speed, port, boat, x, y, containers_capacityacity);
	orders_queue.push(new_order); //adding order to queue
}
/********************************/

/********************************/
Boat &Boat::operator++()
{
	res_pow++;
	return *this;
}
/********************************/
Boat &Boat::operator--()
{
	res_pow--;
	return *this;
}
/********************************/
bool Boat::operator>(const Boat &other) const
{
	return res_pow > other.res_pow;
}
/********************************/
void Boat::update()
{
	if (available)
	{
		if (!orders_queue.empty())
		{
			//start actions for curr order
			Order curr_order = orders_queue.front();
			available = false; //not available for other orders

			switch (curr_order.ord)
			{
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
				attack(curr_order.boat);
				break;
			case (Stop):
				stop();
				break;
			}
		}
		//remove order from queue
		orders_queue.pop();
	}
	else
	{
		switch (status)
		{
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
		case (Move_to_first):
			patrol_move_to_first();
			break;
		case (Stopped):
			available = true;
			break;
		case (Dead):
			//Boat stay in dead status forever
			break;
		}
	}
}
