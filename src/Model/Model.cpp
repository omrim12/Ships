#include "Model.h"
#include "Port.h"
/*************************************/
Model::~Model()	{}
/*************************************/
shared_ptr<Model>& Model::getInstance()	{

    if( inst.get() ) { return inst ; }

    // singleton will be first initialized here
    inst = shared_ptr<Model>(new Model());
    return inst;
}
/*************************************/
vector<shared_ptr<Port>>& Model::getAllPorts()	{ return all_ports;	}
/*************************************/
vector<shared_ptr<Boat>>& Model::getAllBoats()	{ return all_boats; }
/*************************************/
int Model::findPortByLocation(const Location &loc)	{

    for(unsigned int i = 0; i < all_ports.size(); ++i)	{
        if( all_ports[i].get()->get_Location() == loc )	{ return i; }
    }

    return -1;
}
/*************************************/
int Model::findBoatByLocation(const Location& loc)	{

   for(unsigned int i = 0; i < all_boats.size(); ++i)	{
		if( all_boats[i].get()->getLocation() == loc )	{ return i; }
	}

	return -1;

}
/*************************************/
void Model::status()	{ //print status of all objects in the simulation

	for( auto& boat : all_boats )	{ cout << boat << endl; }
	for( auto& port : all_ports )	{ cout << port << endl; }
}
/*************************************/
void Model::go()	{ // loop of "update" for all objects

	for( auto& boat : all_boats )	{ boat.get()->update(); }
	for( auto& port : all_ports )	{ port.get()->update(); }

}
/*************************************/
void Model::create(const string& boat_name, const string& boat_type, int x, int y, int res_atckPower, int cap_range )	{ //add boat to data

	/* RONI IMPLEMENTED
	if( boat_type == "Freighter" )	{ all_boats.push_back(make_shared<Boat>(new freighterBoat() )); }
	else if( boat_type == "Cruiser" )	{ all_boats.push_back(make_shared<Boat>(new Cruiser())); }
	else	{ all_boats.push_back(make_shared<Boat>(new patrolBoat()); }
	*/


}
