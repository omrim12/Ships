#include "Port.h"
#include "patrolBoat.h"
#include "freighterBoat.h"

Port::Port():gameObj(),containers(0),loc(Location()),fuel_capacity(0),ready_to_fuel(queue<unique_ptr<Boat> >{}),
			 	 new_containers(containers),new_fuel_capacity(fuel_capacity){}

Port::~Port()	{}

Port::Port(const Location& loc):gameObj(),containers(0),loc(loc),fuel_capacity(0),ready_to_fuel(queue<unique_ptr<Boat> >{}),
								new_containers(containers),new_fuel_capacity(fuel_capacity)	{}

Location Port::get_Location() const	{ return loc; }

double Port::get_fuel_cap() const	{ return fuel_capacity; }

void Port::set_fuel_cap(double new_cap)	{ fuel_capacity = new_cap; }

void Port::unload(int cont)	{  containers -= cont; }

void Port::load(int cont)	{ containers += cont; }

void Port::fuel(int cap)	{

	/*
	 *
	 *TODO: fuel the top of the queue (use add_fuel of the ship)
	 *
	 */



}

void Port::update()	{

	containers = new_containers;
	fuel_capacity = new_fuel_capacity;
	int required_fuel = ready_to_fuel.front()->getCurrFuel();

	if( required_fuel <= fuel_capacity )	{
		Boat * to_fuel = ready_to_fuel.front().release();
		to_fuel->setCurrFuel(required_fuel);
	}
}

void Port::addToQueue(unique_ptr<Boat>& boat){ ready_to_fuel.push(std::move(boat)); }


