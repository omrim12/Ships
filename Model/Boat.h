#ifndef EX3_BoatS_SIMULATION_Boat_H
#define EX3_BoatS_SIMULATION_Boat_H

#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include "Location.h"
#include "Direction.h"
#include "GameObj.h"
class FreighterBoat;
class CruiserBoat;
class PatrolBoat;
class Model;
class Port;
class Boat;
using namespace std;

enum order
{
	Course,
	Position,
	Destination,
	Dock_at,
	Attack,
	Stop
};
/*****************************************/
enum Status
{
	Stopped,
	Docked,
	Dead,
	Move_to_Course,
	Move_to_Position,
	Move_to_Dest,
	Move_to_first
};

/*****************************************/
struct Order
{
	order ord;
	int deg;
	double speed;
	double x;
	double y;
	weak_ptr<Port> port;
	weak_ptr<Boat> boat;
	int curr_num_of_containers;

	Order(order arg_ord, int arg_deg, double arg_speed, weak_ptr<Port> p, weak_ptr<Boat> b,
		  double arg_x, double arg_y, int containers) : ord(arg_ord), deg(arg_deg), speed(arg_speed), x(arg_x), y(arg_y),
														curr_num_of_containers(containers)
	{
		port = p;
		boat = b;
	};
};

/*****************************************/
struct unload_Port
{
	weak_ptr<Port> port;
	int capacity;

	unload_Port(weak_ptr<Port> p, int cap) : capacity(cap)
	{
		port = p;
	}
};

class Boat : public GameObj
{
protected:
	/*data members*/

	const double MAX_BOAT_FUEL;
	const string name;
	int res_pow; //resistance or attack power
	double curr_fuel;
	Status status;
	double curr_speed;
	Direction direction;
	Location curr_Location;
	Location dest_Location;
	std::weak_ptr<Port> dest_port;
	bool available;

	queue<Order> orders_queue;

public:
	Boat(string &boat_name, double max_fuel = 0, int resPow = 0, int num = 0);

	virtual ~Boat(){};

	Boat(const Boat &) = delete;

	Boat(Boat &&) = delete;

	Boat &operator=(const Boat &) = delete;

	Boat &operator=(Boat &&) = delete;

	static shared_ptr<Boat> createBoat(const string &boat_name, const string &boat_type, int x, int y, int res_atckPower, int cap_range = 0);

	Location getCurrLocation();

	string getName() const;

	double getFuel() const;

	double getMaxFuel() const;

	virtual int getMAXSpeed() = 0;

	void setAvailable(bool b);

	void addFuel(int cap);

	virtual void setWaiting(bool b) = 0;

	virtual void setAskForFuel(bool b) = 0;

	void addOrder(const string &ord_str, int deg = 0, double speed = 0, double x = 0, double y = 0,
				  weak_ptr<Port> port = weak_ptr<Port>(), weak_ptr<Boat> boat = weak_ptr<Boat>(),
				  int containers_capacityacity = 0);

	virtual Boat &operator++();

	virtual Boat &operator--();

	virtual void course(double deg, double speed) = 0;

	virtual void position(double x, double y, double speed) = 0;

	virtual void destination(weak_ptr<Port> port, double speed) = 0;

	virtual void dock(weak_ptr<Port> port) = 0;

	virtual void attack(weak_ptr<Boat> boat) = 0;

	virtual void refuel() = 0;

	virtual void stop() = 0;

	//*inside status functions*
	virtual void in_dock_status() = 0;

	virtual void in_move_status() = 0;

	virtual void patrol_move_to_first() = 0;

	virtual void add_load_dest(weak_ptr<Port> load_port){};

	virtual void add_unload_dest(weak_ptr<Port> unload_port, int capacity){};

	virtual bool operator>(const Boat &other) const;

	virtual void update();
};

#endif
