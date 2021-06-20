#ifndef EX3_BOATS_SIMULATION_MODEL_H
#define EX3_BOATS_SIMULATION_MODEL_H
#include "gameObj.h"
/***********************************/
class Model {
private:
    static unique_ptr<Model> inst;
    vector<shared_ptr<Port>> all_ports;
    vector<shared_ptr<Boat>> all_boats;
    Model(): all_ports(vector<shared_ptr<Port>>()),all_boats(vector<shared_ptr<Boat>>()){};
public:
    static Model& getInstance();
    Model (const Model&) = delete;
    Model& operator = (const Model&) = delete;
    Model(const Model&&) = delete;
    Model& operator= (const Model&&) = delete;
    vector<shared_ptr<Port>>& getAllPorts(){return all_ports;}
    Port& findPortByLocation(const Location &loc);

};
/***********************************/
#endif
