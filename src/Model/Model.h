#ifndef EX3_BOATS_SIMULATION_MODEL_H
#define EX3_BOATS_SIMULATION_MODEL_H
#include "gameObj.h"
#include <vector>
/***********************************/
class Model {

protected:
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
    bool isBoatExist(const string& boat_name );
    bool isPortExist(const string& port_name );
    weak_ptr<Boat> getBoat(const string& boat_name);
    weak_ptr<Boat> getPort(const string& portt_name);

    int findPortByLocation(const Location &loc);
    vector<shared_ptr<Port>>& getAllPorts();
    vector<shared_ptr<Port>>& getAllBoats();

    void status();
    void go();
    void create(const string& boat_name, const string& boat_type, int x, int y, int res_atckPower, int cap_range=0 );

};
/***********************************/
#endif