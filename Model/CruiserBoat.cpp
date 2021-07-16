#include "CruiserBoat.h"
#include "FreighterBoat.h"
/********************************/
void CruiserBoat::course(double deg, double speed)
{
	status = Move_to_Course;
	direction = Direction(deg);
	curr_speed = speed;
}

/********************************/
void CruiserBoat::position(double x, double y, double speed)
{
	status = Move_to_Position;
	direction = Direction(Location(x, y), curr_Location);
	curr_speed = speed;
}

/********************************/
void CruiserBoat::attack(weak_ptr<Boat> attack_boat)
{
	if (attack_range >= curr_Location.distance_from(attack_boat.lock()->getCurrLocation()))
	{
		//any way of attacking -> attack boat stop
		attack_boat.lock()->stop();
		if (*this > *attack_boat.lock())
		{
			//Attack Succeeded
			if (typeid(*attack_boat.lock().get()) == typeid(FreighterBoat()))
			{
				//Case of freighter boat:
				//*attack boat will lose all containers she had
				//*increment cruiser attack power
				dynamic_cast<FreighterBoat *>(attack_boat.lock().get())->setNumOfContainers(0);
				++(*this);
			}
			else if (typeid(*attack_boat.lock().get()) == typeid(PatrolBoat()))
			{
				//Case of patrol boat:
				//*decrement patrol res_pow
				//*increment cruiser attack power
				--(*attack_boat.lock());
				++(*this);
			}
		}
	}
	else
	{
		//Attack Failed
		if (typeid(*attack_boat.lock().get()) == typeid(FreighterBoat()))
		{
			//Case of freighter boat:
			//*decrement cruiser boat power attack
			--(*this);
		}
		else if (typeid(*attack_boat.lock().get()) == typeid(PatrolBoat()))
		{
			//Case of patrol boat:
			//*increment patrol res_pow
			//*decrement cruiser attack power
			++(*attack_boat.lock().get());
			--(*this);
		}
	}
}

/********************************/
void CruiserBoat::in_move_status()
{
	curr_Location = curr_Location.next_Location(direction, curr_speed);
}

/********************************/
ostream &operator<<(ostream &out, const CruiserBoat &ship)
{
	out << ship.name << " at " << ship.curr_Location << ", force: " << ship.res_pow << ", Moving on course "
		<< ship.direction.get_degree() << " deg, speed " << ship.curr_speed << " nm/hr" << endl;
	return out;
}
/************** USED FOR COMPILATION PURPOSES ONLY ****************/

void CruiserBoat::destination(weak_ptr<Port>, double) {}
/********************************/
void CruiserBoat::patrol_move_to_first() {}
/********************************/
void CruiserBoat::dock(weak_ptr<Port>) {}
/********************************/
void CruiserBoat::in_dock_status() {}
/********************************/
void CruiserBoat::refuel() {}
/********************************/
void CruiserBoat::stop() {}
/********************************/
void CruiserBoat::setAskForFuel(bool) {}
/********************************/
void CruiserBoat::setWaiting(bool) {}
/********************************/
int CruiserBoat::getMAXSpeed() { return MAX_SPEED; }
