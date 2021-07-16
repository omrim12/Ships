#ifndef Direction_H_
#define Direction_H_
#include "Location.h"
/*****************************/
class Direction
{ // this class represents a Direction in a euclidean space using two parameters:
	// degree (polar) and vector (cartesian).

private:
	Location vect;
	double degree;

public:
	/* c'tors & d'tors*/
	Direction();
	Direction(double deg);
	Direction(Location &vector);
	Direction(Location &vect, double deg);
	Direction(const Direction &other);
	Direction(Direction &&other);
	Direction(const Location &loc1, const Location &loc2);

	/*operators*/
	Direction &operator=(const Direction &other);
	Direction &operator=(Direction &&other);

	/*setters & getters*/
	Location get_vector() const;
	void set_vector(Location &new_vect);
	int get_degree() const;
	void set_degree(double new_degree);

	/*class functions*/
	Location degree_to_vector(const double deg);
	double vector_to_degree(const Location &loc);
	void normalize();
};
/*****************************/
#endif