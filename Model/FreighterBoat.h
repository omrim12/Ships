#ifndef EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
#define EX3_BOATS_SIMULATION_FREIGHTERBOAT_H
#include "Boat.h"

enum dest_type
{
	load,
	unload,
	None
};
/*****************************************/
class FreighterBoat : public Boat
{
private:
	/*constants*/
	const int MAX_CONTAINERS_CAPACITY;
	static const int MAX_FRI_FUEL = 500000;
	const int MAX_SPEED = 40;
	const double FUEL_PER_NM = 1000;
	int curr_num_of_containers;
	bool waiting_in_fuel_queue;
	bool ask_fuel;
	dest_type type;

	vector<weak_ptr<Port>> ports_to_load;
	vector<unload_Port> ports_to_unload;

public:
	/*c'tors & d'tors*/
	FreighterBoat(string boat_name, int containers_capacity, int res);
	~FreighterBoat() {}

	void setNumOfContainers(int n);
	/*class functions*/
	void load_boat();
	void unload_boat();
	void course(double deg, double speed);

	void position(double x, double y, double speed);

	void destination(weak_ptr<Port> port, double speed);

	void dock(weak_ptr<Port> port);

	void attack(weak_ptr<Port> port);

	void refuel();

	void stop();

	void in_dock_status();

	void in_move_status();

	void patrol_move_to_first();

	void attack(weak_ptr<Boat>);

	void setWaiting(bool b);

	void setAskForFuel(bool b);

	int getMAXSpeed();

	bool dest_is_load(weak_ptr<Port> dest);

	bool dest_is_unload(weak_ptr<Port> dest);

	void add_load_dest(weak_ptr<Port> load_port);

	void add_unload_dest(weak_ptr<Port> unload_port, int capacity);

	/*print operator*/
	friend ostream &operator<<(ostream &out, const FreighterBoat &ship);
};

#endif
