#ifndef EX3_BOATS_SIMULATION_VIEW_H
#define EX3_BOATS_SIMULATION_VIEW_H
#include "../Model/Model.h"
/***************************/
class View
{ // This class represents the view component of this simulation.
	// it simulates a map of the current game objects condition
	// which is defined by scale, size and other defaultive interfaces
	// using ASCII - based graphics.

	const int DEFAULT_MAP_SIZE = 25;
	const int DEFAULT_MAP_SCALE = 2;
	const int MAX_MAP_SIZE = 30;
	const int MIN_MAP_SIZE = 6;
	Location axis_base;
	int map_size;
	double scale;

public:
	/*exceptions*/
	class invalid_size_exception : public exception
	{
	public:
		const char *what() const noexcept
		{
			return "ERROR: illegal map size given.";
		}
	};

	/*c'tors & d'tors*/
	View();
	~View();

	/*class functions*/
	void show();
	void _default();
	void size(int n);
	void zoom(double);
	void pan(double x, double y);
};
/***************************/
#endif
