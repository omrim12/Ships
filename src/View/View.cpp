#include "View.h"
/***********************************/
View::View():axis_base(Location(0,0)),map_size(DEFAULT_MAP_SIZE),scale(DEFAULT_MAP_SCALE)	{}
/***********************************/
View::~View()	{}
/***********************************/
void View::show()	{

	// display show status
	cout << endl << "Display size: " << map_size << ", scale: " << scale << ", origin: " << axis_base << endl;

	int boat_index = -1;

	/*
	 *
	 *
	 *
	 * TODO: calculate nested for loop variables in order to
	 * 		 output the correct map.
	 * 		 make sure that interfacing with game objects from
	 * 		 model singleton is working successfully.
	 *
	 *
	 */


}
/***********************************/
void View::_default()	{
	map_size = DEFAULT_MAP_SIZE;
}
/***********************************/
void View::size(int n)	{
	if( n > MAX_MAP_SIZE || n < MIN_MAP_SIZE )	{
		/*
		 *
		 * TODO: handle exception/error message here !
		 *
		 */
		return; // will be removed if an exception will be thrown.
	}

	map_size = n;
}
/***********************************/
void View::zoom(double new_scale)	{ scale = new_scale; }
/***********************************/
void View::pan(double x, double y)	{ axis_base = Location(x,y); }
/***********************************/
