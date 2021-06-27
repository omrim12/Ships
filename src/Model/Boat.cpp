#include "Boat.h"
/********************************/
Location Boat::getCurrLocation(){return curr_Location;}
/********************************/
string Boat::getName() const	{ return name; }
/********************************/
void Boat::setAvailable(bool b) { available = b; }
/********************************/
void Boat::setWaiting(bool b) { waiting_in_fuel_queue = b; }
/********************************/
void Boat::setAskForFuel(bool b) { ask_fuel = b; }
/********************************/
void Boat::addFuel(int cap) { curr_fuel += cap; }
/********************************/
void Boat::addOrder(const string &ord_str, int deg, double speed, double x, double y, weak_ptr<Port> port, weak_ptr<Boat> boat,
         int containers_capacityacity) {
    order curr_ord;
    if (ord_str == "course") curr_ord = Course;
    else if (ord_str == "position") curr_ord = Position;
    else if (ord_str == "destination") curr_ord = Destination;
    else if (ord_str == "dock_at") curr_ord = Dock_at;
    else if (ord_str == "attack") curr_ord = Attack;
    else curr_ord = Stop;

    Order new_order = Order(curr_ord, deg, speed, port, boat, x, y, containers_capacityacity);
    orders_queue.push(new_order);   //adding order to queue
}
/********************************/

/********************************/
Boat& Boat::operator++() {
    res_pow++;
    return *this;
}
/********************************/
Boat& Boat::operator--() {
    res_pow--;
    return *this;
}
/********************************/
bool Boat::operator>(const Boat &other) const{
    return res_pow > other.res_pow;
}
/********************************/
void Boat::update() {
    if (available) {
        if (!orders_queue.empty()) {
            //start actions for curr order
            Order curr_order = orders_queue.front();
            available = false; //not available for other orders

            switch (curr_order.ord) {
                case (Course):
                    course(curr_order.deg, curr_order.speed);
                    break;
                case (Position):
                    position(curr_order.x, curr_order.y, curr_order.speed);
                    break;
                case (Destination):
                    destination(curr_order.port, curr_order.speed);
                    break;
                case (Dock_at):
                    dock(curr_order.port);
                    break;
                case (Attack):
                    attack(curr_order.boat);
                    break;
                case (Stop):
                    stop();
                    break;
            }
        }
        //remove order from queue
        orders_queue.pop();
    } else {
        switch (status) {
            case (Docked):
                in_dock_status();
                break;
            case (Move_to_Dest):
                in_move_status();
                break;
            case (Move_to_Course):
                in_move_status();
                break;
            case (Move_to_Position):
                in_move_status();
                break;
            case(Move_to_first):
                patrol_move_to_first();
                break;
            case (Stopped):
                available = true;
                break;
            case (Dead):
                //Boat stay in dead status forever
                break;
        }
    }
}
