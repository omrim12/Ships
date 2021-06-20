#include "Port.h"
#include "patrolBoat.h"
#include "freighterBoat.h"
/********************************************/
Port::Port(): gameObj(), loc(Location(50,5)), containers(0),port_name("Nagoya"),fuel_capacity(1000000),
						 fuel_product_per_hr(1000),ready_to_fuel(queue<weak_ptr<Boat> >{}),
						 new_containers(containers),new_fuel_capacity(fuel_capacity){} // for default port Nagoya.
/********************************************/
Port::Port(Port&& other):gameObj(),loc(other.loc), containers(other.containers),port_name(other.port_name),fuel_capacity(other.fuel_capacity),
						 fuel_product_per_hr(other.fuel_product_per_hr), ready_to_fuel(other.ready_to_fuel), new_containers(other.new_containers),
						 new_fuel_capacity(other.new_fuel_capacity)	{}
/********************************************/
Port::Port(const Port& other):gameObj(),loc(other.loc), containers(other.containers),port_name(other.port_name),fuel_capacity(other.fuel_capacity),
		 fuel_product_per_hr(other.fuel_product_per_hr), ready_to_fuel(other.ready_to_fuel), new_containers(other.new_containers),
		 new_fuel_capacity(other.new_fuel_capacity)	{}
/********************************************/
Port::Port(double fuel_capacity, double fuel_product, string& name, const Location& loc):
				gameObj(),loc(Location()),containers(0),port_name(name),fuel_capacity(fuel_capacity),
				fuel_product_per_hr(fuel_product),ready_to_fuel(queue<weak_ptr<Boat> >{}),new_containers(containers),
				new_fuel_capacity(fuel_capacity){}
/********************************************/
Port::~Port()	{}
/********************************************/
Port& Port::operator=(const Port& other)	{

	loc = other.loc;
	containers = other.containers;
	port_name = other.port_name;
	fuel_capacity = other.fuel_capacity;
	fuel_product_per_hr = other.fuel_product_per_hr;
	ready_to_fuel = other.ready_to_fuel;
	new_containers = other.new_containers;
	new_fuel_capacity = other.new_fuel_capacity;

	return *this;
}
/********************************************/
Port& Port::operator=(Port&& other)	{

	loc = other.loc;
	containers = other.containers;
	port_name = other.port_name;
	fuel_capacity = other.fuel_capacity;
	fuel_product_per_hr = other.fuel_product_per_hr;
	ready_to_fuel = other.ready_to_fuel;
	new_containers = other.new_containers;
	new_fuel_capacity = other.new_fuel_capacity;

	return *this;
}
/********************************************/
Location Port::get_Location() const	{ return loc; }
/********************************************/
string Port::getPortName() const	{ return port_name; }
/********************************************/
double Port::get_fuel_cap() const	{ return fuel_capacity; }
/********************************************/
void Port::unload(int cont)	{  containers -= cont; }
/********************************************/
void Port::load(int cont)	{ containers += cont; }
/********************************************/
void Port::fuel()	{

	double required_fuel = ready_to_fuel.front().lock()->getMaxFuel() - ready_to_fuel.front().lock()->getCurrFuel();

	// check if fuel action is valid
	if( required_fuel <= fuel_capacity )	{

		ready_to_fuel.front().lock()->setCurrFuel(required_fuel);
		new_fuel_capacity = fuel_capacity - required_fuel;
		ready_to_fuel.pop();

	}
}
/********************************************/
void Port::addToQueue(weak_ptr<Boat> boat){ ready_to_fuel.push(boat); }
/********************************************/
void Port::update()	{

	containers = new_containers;
	fuel_capacity = new_fuel_capacity;
	/*
	 *
	 * to update :
	 *
	 * 1. fuel
	 * 3. product more fuel
	 *
	 */

}
/********************************************/

