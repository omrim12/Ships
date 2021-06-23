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
/////*************************************/
//vector<shared_ptr<Port>>& Model::getAllBoats()	{ return all_boats; }
///*************************************/
//int Model::findPortByLocation(const Location &loc)	{
//
//    for(int i = 0; i < all_ports.size(); ++i)	{
//        if( all_ports[i].get()->get_Location() == loc )	{
//            all_ports[i].get();
//            return i;
//        }
//    }
//
//    return -1;
//}
/*************************************/

void Model::status(){} //print status of all objects in the simulation
void Model::go(){}       //loop of "update" for all objects
void Model::create(const string& boat_name, const string& boat_type, int x, int y, int res_atckPower, int cap_range ){} //add boat to data