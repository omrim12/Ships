#ifndef Port_H_
#define Port_H_
#include "GameObj.h"
/**************************/
class Boat;
/**************************/
class Port : public gameObj	{

private:
    /*data members*/
    Location loc;
    int containers;
    string port_name;
    double fuel_capacity;
    double fuel_product_per_hr;
    queue< weak_ptr<Boat> > ready_to_fuel;

    /*data members update*/
    int new_containers;
    double new_fuel_capacity;

public:
    /*c'tors & d'tors*/
    Port();
    ~Port();
    Port(Port&& other);
    Port(const Port& other);
    Port(double fuel_capacity, double fuel_product, string& name, const Location& loc);

    /*operators*/
    Port& operator=(Port&&);
    Port& operator=(const Port&);

    /*setters & getters*/
    string getPortName() const;
    double get_fuel_cap() const;
    Location get_Location() const;
    void addToQueue(weak_ptr<Boat> boat);

    /*class functions*/
    void load(int cap);
    void fuel();
    void unload(int cap);
    virtual void update();
};
/**************************/
#endif