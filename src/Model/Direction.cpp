#include "Direction.h"
/******************************************/
Direction::Direction():vect(Location()),degree(0)	{}
/******************************************/
Direction::Direction(double deg):vect(degree_to_vector(deg)),degree(deg)	{normalize();}
/******************************************/
Direction::Direction(Location& vector):vect(vector),degree(vector_to_degree(vector))	{normalize();}
/******************************************/
Direction::Direction(Location& vect, double deg):vect(vect),degree(deg)	{normalize();}
/******************************************/
Direction::Direction(const Direction& other):vect(other.vect),degree(other.degree)	{}
/******************************************/
Direction::Direction(Direction&& other):vect(other.vect),degree(other.degree)	{}
/******************************************/
Direction& Direction::operator=(const Direction& other)	{
	vect = other.vect;
	degree = other.degree;
	return *this;
}
/******************************************/
Direction::Direction(const Location& loc1, const Location& loc2):vect(Location()),degree(0)	{
    vect.set_x(loc1.get_x() - loc2.get_x());
    vect.set_y(loc1.get_y() - loc2.get_y());
    degree = vector_to_degree(vect);
    normalize();
}
/****************************************/
Direction& Direction::operator=(Direction&& other)	{
	vect = other.vect;
	degree = other.degree;
	return *this;
}
/******************************************/
Location Direction::get_vector() const	{ return vect; }
/******************************************/
void Direction::set_vector(Location& new_vect)	{ vect = new_vect; }
/******************************************/
int Direction::get_degree() const	{ return degree; }
/******************************************/
void Direction::set_degree(double new_degree)	{ degree = new_degree; }
/******************************************/
Location Direction::degree_to_vector(const double deg)	{
	return Location(sin(deg),cos(deg)); // derives from identity : y = sin(degree), x = cos(degree)
}
/******************************************/
double Direction::vector_to_degree(const Location& loc)	{return atan(loc.get_y()/loc.get_x());}
														// derives from calculation: vector's degree = arctan(sin(degree) / cos(degree))
														//											 = arctan(y/x)
/******************************************/
void Direction::normalize()	{
	double vect_size = sqrt(pow(vect.get_x(),2) + pow(vect.get_y(),2));
	if( vect_size <= 1 )	{ return; } // already normalized / no Direction
	vect = Location(vect.get_x() / vect_size, vect.get_y() / vect_size );
}
