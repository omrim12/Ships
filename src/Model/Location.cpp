#include "Location.h"
#include "Direction.h"
/****************************************/
Location::Location() : x(0), y(0) {}

/****************************************/
Location::Location(double x, double y) : x(x), y(y) {}

/****************************************/
Location::Location(const Location &other) : x(other.x), y(other.y) {}

/****************************************/
Location::Location(Location &&other) : x(other.x), y(other.y) {}

/****************************************/
Location::~Location() {}

/****************************************/
Location &Location::operator=(const Location &other) {
    x = other.x;
    y = other.y;
    return *this;
}

/****************************************/
Location &Location::operator=(Location &&other) {
    x = other.x;
    y = other.y;
    return *this;
}

/****************************************/
bool Location::operator !=(const Location& other)	{
	if( x != other.x || y != other.y )	{ return true; }
	return false;
}
/****************************************/
void Location::set_x(double new_x) { x = new_x; }

/****************************************/
void Location::set_y(double new_y) { y = new_y; }

/****************************************/
int Location::get_x() const { return x; }

/****************************************/
int Location::get_y() const { return y; }

/****************************************/
Location Location::next_Location(const Direction &direct, double velocity) const {

    Location new_loc;
    new_loc.set_x(x + velocity*direct.get_vector().x);
    new_loc.set_y(y + velocity*direct.get_vector().y);

    return new_loc;
}

double Location::distance_from(const Location &loc) { return sqrt(pow(x - loc.x, 2) + pow(y - loc.y, 2)); }

/****************************************/
