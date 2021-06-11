#ifndef Port_H_
#define Port_H_
#include <memory>
#include <queue>
#include "Boat.h"
#include "GameObj.h"
class Boat;
/**************************/
class Port : public gameObj	{

private:
	/*data members*/
	Location loc;
	double fuel_capacity;
	queue< unique_ptr<Boat> > ready_to_fuel;

	/*data members update*/
	double new_fuel_capacity;

public:
	/*c'tors & d'tors*/
	Port();
	Port(const Location& loc);
	void addToQueue(unique_ptr<Boat>& boat){ready_to_fuel.push(std::move(boat));}
	~Port();

	/*operators*/







	/*setters & getters*/
	Location get_Location() const;
	double get_fuel_cap() const;
	void set_fuel_cap(double new_cap);


	/*class functions*/
	void unload(int cap);
	void load(int cap);
	void fuel(int cap);
	virtual void update();
};
/**************************/
#endif
