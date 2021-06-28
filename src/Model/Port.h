#ifndef Port_H_
#define Port_H_

#include <deque>
#include <memory>
#include <string>

#include "Boat.h"
#include "Location.h"

/**********/
class Boat;
class patrolBoat;
/**********/
class Port : public gameObj	{

private:
    /*data members*/
    Location loc;
    int containers;
    string port_name;
    double fuel_capacity;
    double fuel_product_per_hr;
    deque < weak_ptr<Boat> > ready_to_fuel;

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
    bool operator==(const Port &p);

    /*setters & getters*/
    string getPortName() const;
    double get_fuel_cap() const;
    Location get_Location() const;
    void addToQueue(weak_ptr<Boat> boat);
    void removeFromQueue(weak_ptr<Boat> boat);
    bool readyToFuelEmpty();

    /*class functions*/
    void load_port(int cap);
    void fuel();
    void fuel(patrolBoat& boat);
    void unload_port(int cap);
    virtual void update();
};
/**********/
#endif
