#include "Boat.h"
#include "Port.h"
#include "patrolBoat.h"
#include "freighterBoat.h"
/********************************************/
Port::Port(): gameObj(), loc(Location(50,5)), containers(0),port_name("Nagoya"),fuel_capacity(1000000),
              fuel_product_per_hr(1000),ready_to_fuel(deque<weak_ptr<Boat> >{}){} // for default port Nagoya.
/********************************************/
Port::Port(Port&& other):gameObj(),loc(other.loc), containers(other.containers),port_name(other.port_name),fuel_capacity(other.fuel_capacity),
                         fuel_product_per_hr(other.fuel_product_per_hr), ready_to_fuel(other.ready_to_fuel)
                        {}
/********************************************/
Port::Port(const Port& other):gameObj(),loc(other.loc), containers(other.containers),port_name(other.port_name),fuel_capacity(other.fuel_capacity),
                              fuel_product_per_hr(other.fuel_product_per_hr), ready_to_fuel(other.ready_to_fuel){}
/********************************************/
Port::Port(double fuel_capacity, double fuel_product, string& name, const Location& loc):
        gameObj(),loc(Location()),containers(0),port_name(name),fuel_capacity(fuel_capacity),
        fuel_product_per_hr(fuel_product),ready_to_fuel(deque<weak_ptr<Boat> >{}){}
/********************************************/
Port::~Port()	{}
/********************************************/
bool Port::readyToFuelEmpty(){
    return ready_to_fuel.empty();
}
/********************************************/
Port& Port::operator=(const Port& other)	{

    loc = other.loc;
    containers = other.containers;
    port_name = other.port_name;
    fuel_capacity = other.fuel_capacity;
    fuel_product_per_hr = other.fuel_product_per_hr;
    ready_to_fuel = other.ready_to_fuel;

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

    return *this;
}
/********************************************/
Location Port::get_Location() const	{ return loc; }
/********************************************/
string Port::getPortName() const	{ return port_name; }
/********************************************/
double Port::get_fuel_cap() const	{ return fuel_capacity; }
/********************************************/
void Port::unload_port(int cont)	{  containers -= cont; }
/********************************************/
void Port::load_port(int cont)	{ containers += cont; }
/********************************************/
void Port::fuel()	{

    double required_fuel = ready_to_fuel.front().lock()->getMaxFuel() - ready_to_fuel.front().lock()->getFuel();

    // check if fuel action is valid
    if( required_fuel <= fuel_capacity )	{

        ready_to_fuel.front().lock()->setAddFuel(required_fuel);
        new_fuel_capacity = fuel_capacity - required_fuel;
        ready_to_fuel.pop_front();

    }
}
/********************************************/ // TODO: WHICH IMPLEMENTATION IS UP TO DATE ? (ABOVE OR DOWN)
void Port::fuel(patrolBoat& boat){

    double required_fuel = boat.getMaxFuel() - boat.getFuel();

    // check if fuel action is valid
    if( required_fuel <= fuel_capacity )	{

        boat.addFuel(required_fuel);
        boat.setWaiting(false);
        boat.setAvailable(true);
        fuel_capacity -= required_fuel;
    }
}

/********************************************/
void Port::addToQueue(weak_ptr<Boat> boat){ ready_to_fuel.push_back(boat); }
/********************************************/
void Port::removeFromQueue(weak_ptr<Boat> boat){
    for(auto it = ready_to_fuel.begin(); it != ready_to_fuel.end(); it++)   {
        if((*it).lock()->getName() == boat.lock()->getName()){
            ready_to_fuel.erase(it);
            return;
        }
    }
}
/********************************************/
void Port::update()	{

    fuel();
    fuel_capacity += fuel_product_per_hr;

}
/********************************************/
