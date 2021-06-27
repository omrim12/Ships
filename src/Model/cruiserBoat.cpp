#include "cruiserBoat.h"

/********************************/
void cruiserBoat::course(double deg, double speed) {
    status = Move_to_Course;
    direction = direction(deg);
    curr_speed = speed;
}

/********************************/
void cruiserBoat::position(double x, double y, double speed) {
    status = Move_to_Position;
    direction = Direction(Location(x,y),curr_Location);
    curr_speed = speed;
}

/********************************/
void cruiserBoat::attack(weak_ptr<Boat> attack_boat) {
    if (attack_range >= curr_Location.distance_from(attack_boat.lock()->getCurrLocation())) {
        //any way of attacking -> attack boat stop
        attack_boat.lock()->stop();
        if (this > (*attack_boat)) {
            //Attack Succeeded
            if (typeid(*attack_boat) == typeid(freighterBoat())) {
                //Case of freighter boat:
                //*attack boat will lose all containers she had
                //*increment cruiser attack power
                attack_boat.lock().get()->setNumOfContainers(0);
                this++;

            } else if (typeid(*attack_boat) == typeid(patrolBoat())) {
                //Case of patrol boat:
                //*decrement patrol res_pow
                //*increment cruiser attack power
                (*attack_boat)--;
                this++;

            }
        }
    } else {
        //Attack Failed
        if (typeid(*attack_boat) == typeid(freighterBoat())) {
            //Case of freighter boat:
            //*decrement cruiser boat power attack
            this--;

        } else if (typeid(*attack_boat).name() == typeid(patrolBoat()).name()) {
            //Case of patrol boat:
            //*increment patrol res_pow
            //*decrement cruiser attack power
            (*attack_boat)++;
            this--;

        }

    }
}

/********************************/
void cruiserBoat::in_move_status() {
    curr_Location = curr_Location.next_Location(direction, curr_speed);
}


/********************************/
ostream &operator<<(ostream &out, const cruiserBoat &ship) {
    out << ship.name << " at " << ship.curr_Location << ", force: " << ship.res_pow << ", Moving on course "
        << ship.direction.get_degree() << " deg, speed " << ship.curr_speed << " nm/hr" << endl;
    return out;
}
/********************************/

