#ifndef Location_H_
#define Location_H_
#include <cmath>
#include <queue>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
/************************************/
class Direction;
/************************************/
class Location	{ // this class represents a point in a euclidean space.

private:
	int x;
	int y;

public:
	/* c'tors & d'tors*/
	Location();
	Location(double x, double y);
	Location(const Location& other);
	Location(Location&& other);
	~Location();

	/*operators*/
	Location& operator=(const Location& other);
	Location& operator=(Location&& other);

	/*setters & getters*/
	void set_x(double new_x);
	void set_y(double new_y);
	int get_x() const;
	int get_y() const;

	/*class functions*/
	Location next_Location(const Direction& direct, double velocity) const;
	double distance_from(const Location &loc);

	/*print operator*/
	friend ostream& operator<<(ostream& out, const Location& loc)	{
		out << "(" << loc.x << "," << loc.y << ")";
		return out;
	}
};
/***********************************/
#endif
