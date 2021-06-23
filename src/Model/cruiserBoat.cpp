//
// Created by User on 11/06/2021.
//

#include "cruiserBoat.h"

void cruiserBoat::attackNextTick(weak_ptr<Boat>& boat){
    to_attack=true;
    attack_boat = boat;
}

void cruiserBoat::attack_now(){
    if(attack_range >= curr_Location.distance_from(attack_boat.lock()->getCurrLocation())){
        attack_boat.lock()->stop();
    }
    if(attack_range >= curr_Location.distance_from(attack_boat.lock()->getCurrLocation())){
        if(attack_power > attack_boat.lock()->getResistance())  {
            //Attack Succeeded
            if(typeid(*attack_boat).name() == typeid(freighterBoat()).name()){
                //Case of freighter boat:
                //*attack boat will lose all containers she had
                //*increment cruiser attack power
                attack_boat.lock().get()->setNumOfContainers(0);
                attack_power++;

            }
            else if(typeid(*attack_boat).name() == typeid(patrolBoat()).name()){
                //Case of patrol boat:
                //*decrement patrol resistance
                //*increment cruiser attack power
                attack_boat.lock()->operator--();
                attack_power++;

            }
        }
    }
    else{
        //Attack Failed
        if(typeid(*attack_boat).name() == typeid(freighterBoat()).name()){
            //Case of freighter boat:
            //*decrement cruiser boat power attack
            attack_power--;

        }
        else if(typeid(*attack_boat).name() == typeid(patrolBoat()).name()){
            //Case of patrol boat:
            //*increment patrol resistance
            //*decrement cruiser attack power
            attack_boat.lock()->operator++();
            attack_power--;

        }

    }
}

///***in general update - make sure cruiser boat attack will be at the end

void cruiserBoat::update() {
    ///implements***


}


ostream &operator<<(ostream &out, const cruiserBoat &ship) {
    out << ship.name << " at " << ship.curr_Location << ", force: " << ship.attack_power << ", Moving on course "
        << ship.direction.get_degree() << " deg, speed " << ship.curr_speed << " nm/hr" << endl;
    return out;
}


