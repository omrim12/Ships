#ifndef EX3_BOATS_SIMULATION_MODEL_H
#define EX3_BOATS_SIMULATION_MODEL_H
#include "gameObj.h"
#include <vector>
/***********************************/
class Model {

private:
    static unique_ptr<Model> inst;
    vector<shared_ptr<Port>> all_ports;
    vector<shared_ptr<Boat>> all_boats;
    Model(): all_ports(vector<shared_ptr<Port>>()),all_boats(vector<shared_ptr<Boat>>()){}; // user creation is forbidden.

public:
    /*exceptions*/


    /*c'tors & d'tors*/
    Model (const Model&) = delete;
    Model(const Model&&) = delete;

    /*operators*/
    Model& operator = (const Model&) = delete;
    Model& operator= (const Model&&) = delete;

    /*class functions*/
    static Model& getInstance();
    int findPortByLocation(const Location &loc);
    vector<shared_ptr<Port>>& getAllPorts();
    vector<shared_ptr<Port>>& getAllBoats();

};
/***********************************/
#endif