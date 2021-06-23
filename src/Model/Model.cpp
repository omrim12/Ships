#include "Model.h"
/*************************************/
Model& Model::getInstance()	{

    if( inst.get() ) { return *inst.get(); }

    // singleton will be first initialized here
    inst = unique_ptr<Model>(new Model());
    return *inst.get();
}
/*************************************/
vector<shared_ptr<Port>>& Model::getAllPorts()	{ return all_ports;	}
/*************************************/
vector<shared_ptr<Port>>& Model::getAllBoats()	{ return all_boats; }
/*************************************/
int Model::findPortByLocation(const Location &loc)	{

    for(int i = 0; i < all_ports.size(); ++i)	{
        if( all_ports[i].get()->get_Location() == loc )	{
            return i;
        }
    }

    return -1;
}
/*************************************/