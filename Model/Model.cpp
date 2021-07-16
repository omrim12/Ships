#include "Model.h"

#include <iostream>
#include <memory>
#include <string>

#include "Location.h"
#include "Port.h"
#include "Boat.h"
/*************************************/
shared_ptr<Model> Model::inst = nullptr;
Model::Model() : all_ports(), all_boats(){};
Model::~Model() {}

/*************************************/
shared_ptr<Model> &Model::getInstance()
{

	if (inst.get())
	{
		return inst;
	}

	// singleton will be first initialized here
	inst = shared_ptr<Model>(new Model());
	return inst;
}

/*************************************/
vector<shared_ptr<Port>> &Model::getAllPorts() { return all_ports; }

/*************************************/
vector<shared_ptr<Boat>> &Model::getAllBoats() { return all_boats; }
/*************************************/
void Model::status()
{ //print status of all objects in the simulation

	for (auto &boat : all_boats)
	{
		cout << boat << endl;
	}
	for (auto &port : all_ports)
	{
		cout << port << endl;
	}
}
/*************************************/
void Model::go()
{ // loop of "update" for all objects

	for (auto &boat : all_boats)
	{
		boat.get()->update();
	}
	for (auto &port : all_ports)
	{
		port.get()->update();
	}
}

bool Model::isBoatExist(const string &boat_name)
{
    for(auto& b: all_boats){
        if(b.get()->getName() == boat_name)return true;
    }
	return false;
};

bool Model::isPortExist(const string &port_name)
{
    for(auto& p: all_ports){
        if(p.get()->getPortName() == port_name)return true;
    }
	return false;
};

weak_ptr<Boat> Model::getBoat(const string &boat_name)
{
    for(auto& b: all_boats){
            if(b.get()->getName() == boat_name)return b;
    }
    return this->all_boats[0];

};

weak_ptr<Port> Model::getPort(const string &port_name)
{
    for(auto& p: all_ports){
        if(p.get()->getPortName() == port_name)return p;
    }
	return this->all_ports[0];
};
/*************************************/
void Model::create(const string &boat_name, const string &boat_type, int x, int y, int res_pow, int cap_range)
{
	//add boat to data
	all_boats.push_back(Boat::createBoat(boat_name, boat_type, x, y, res_pow, cap_range));
	//    if (boat_type == "Freighter") {
	//        shared_ptr<Boat> new_boat (new freighterBoat(boat_name, cap_range, res_pow));
	//        all_boats.push_back(new_boat);
	//    }
	//    else if (boat_type == "Cruiser") { all_boats.push_back(shared_ptr<Boat>(new cruiserBoat(boat_name,res_pow,cap_range))); }
	//    else { all_boats.push_back(shared_ptr<Boat>(new patrolBoat(boat_name,res_pow))); }
}
