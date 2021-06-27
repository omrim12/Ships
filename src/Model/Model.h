#ifndef EX3_BOATS_SIMULATION_MODEL_H
#define EX3_BOATS_SIMULATION_MODEL_H
#include "gameObj.h"
#include <vector>
/***********************************/
class Model {

protected:
    static shared_ptr<Model> inst;
    vector<shared_ptr<Port>> all_ports;
    vector<shared_ptr<Boat>> all_boats;
    Model(): all_ports(vector<shared_ptr<Port>>()),all_boats(vector<shared_ptr<Boat>>()){}; // user creation is forbidden.

public:
    /*exceptions*/
    /*c'tors & d'tors*/
    ~Model();
    Model (const Model&) = delete;
    Model(const Model&&) = delete;

    /*operators*/
    Model& operator = (const Model&) = delete;
    Model& operator= (const Model&&) = delete;

    /*class functions*/
    static shared_ptr<Model>& getInstance();
    bool isBoatExist(const string& boat_name );
    bool isPortExist(const string& port_name );
    weak_ptr<Boat> getBoat(const string& boat_name);
    weak_ptr<Port> getPort(const string& port_name);

    int findPortByLocation(const Location &loc);
    int findBoatByLocation(const Location& loc);
    vector<shared_ptr<Port>>& getAllPorts();
    vector<shared_ptr<Boat>>& getAllBoats();

    void go();
    void status();
    void create(const string& boat_name, const string& boat_type, int x, int y, int res_atckPower, int cap_range = 0 );

};
/***********************************/
#endif
