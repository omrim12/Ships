//
// Created by User on 19/06/2021.
//

#ifndef EX3_BOATS_SIMULATION_MODEL_H
#define EX3_BOATS_SIMULATION_MODEL_H
#include "Port.h"
#include "Boat.h"
#include <vector>



class Model {
private:
    static unique_ptr<Model> inst;
    vector<shared_ptr<Port>> all_ports;
    vector<unique_ptr<Boat>> all_boats;
    Model(): all_ports(vector<shared_ptr<Port>>()),all_boats(vector<unique_ptr<Boat>>()){};
public:
    static Model& getInstance();
    Model (const Model&) = delete;
    Model& operator = (const Model&) = delete;
    Model(const Model&&) = delete;
    Model& operator= (const Model&&) = delete;
    vector<shared_ptr<Port>>& getAllPorts(){return all_ports;}
    Port& findPortByLocation(const Location &loc);

};


#endif //EX3_BOATS_SIMULATION_MODEL_H
