#include "View.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "../Model/Boat.h"
#include "../Model/Location.h"
/***********************************/
View::View():axis_base(Location(-10,-10)),map_size(DEFAULT_MAP_SIZE),scale(DEFAULT_MAP_SCALE)	{}
/***********************************/
View::~View()	{}
/***********************************/
int num_length(int number)	{

	int length = 0;

	if( number < 0 )	{ ++length; }

	number = abs(number);

	while( number / 10 )	{
		++length;
		number /= 10;
	}

	++length; // counting last digit
	return length;
}
/***********************************/
void print_multiple(char c, int times)	{ while( times-- )	{ cout << c; } }
/***********************************/
void View::show()	{

	// display show status
	cout << fixed << setprecision(2) << "Display size: " << map_size << ", scale: " << scale << ", origin: " << axis_base << endl;
	cout << fixed << setprecision(0);
	int count = 0;
	int line_display;
	int curr_disp_len;
	int max_length = 4;
	int boat_index = -1;
	bool signed_boats[Model::getInstance()->all_boats.size()];
	for(unsigned int i = 0; i < Model::getInstance()->all_boats.size(); ++i)	{ signed_boats[i] = false; }

	for(int i = 0; i < map_size; i++)	{

		line_display = int(axis_base.y + ((map_size - 1) * scale) - 3 * count * scale);
		curr_disp_len = num_length(line_display);

		if( !(i % 3) )	{ // record line display every third line
			// --line gaps calculations--
			if( max_length < curr_disp_len )	{ max_length = curr_disp_len; }

			print_multiple(' ',max_length - curr_disp_len);

			// --print out line display
			cout << line_display;
			++count;
		}

		else	{ print_multiple(' ',max_length); }

		for(int j = 0; j < map_size; j++)	{

			boat_index = -1;

			for(unsigned int k = 0; k < Model::getInstance()->all_boats.size(); ++k)	{

				if( Model::getInstance()->all_boats[k]->getLocation().get_y() == axis_base.y + (map_size - i) * scale &&
						Model::getInstance()->all_boats[k]->getLocation().get_x() == axis_base.x + j * scale  )	{
					if( !signed_boats[k] )	{
						boat_index = k;
						cout << Model::getInstance()->all_boats[k]->getName().substr(0,2);
						signed_boats[k] = true;
					}
				}


				if( Model::getInstance()->all_boats[k]->getLocation().get_y() >= axis_base.y + (map_size - (i + 1)) * scale &&
					Model::getInstance()->all_boats[k]->getLocation().get_y() < axis_base.y + (map_size - i) * scale &&
					Model::getInstance()->all_boats[k]->getLocation().get_x() >= axis_base.x + (j - 1) * scale &&
					Model::getInstance()->all_boats[k]->getLocation().get_x() < axis_base.x + j * scale )	{
						if( !signed_boats[k] )	{
							boat_index = k;
							cout << Model::getInstance()->all_boats[k]->getName().substr(0,2);
							signed_boats[k] = true;
						}
				}

			}

			if( boat_index == -1 )	{ cout << ". "; }
		}
		cout << endl;

	}

	print_multiple(' ',max_length); // for x axis symmetry
	count = 0;

	for(int i = 0; i < map_size; ++i)	{

		if( !(i % 3) )	{ // record column display every third column
			if( i != 0 )	{
				cout.width(num_length(axis_base.x + 3 * count * scale) + 4); }
			cout << axis_base.x + 3 * count * scale;
			++count;
		}
		/*
		 *
		 *
		 * TODO : fix row output width to match map size.
		 *
		 *
		 */
	}
	cout << endl;
}
/***********************************/
void View::_default()	{
	map_size = DEFAULT_MAP_SIZE;
	scale = DEFAULT_MAP_SCALE;
	axis_base = Location(-10,-10);
}
/***********************************/
void View::size(int n) throw(invalid_size_exception)	{
	if( n > MAX_MAP_SIZE || n < MIN_MAP_SIZE )	{
		throw( invalid_size_exception() );
	}

	map_size = n;
}
/***********************************/
void View::zoom(double new_scale)	{ scale = new_scale; }
/***********************************/
void View::pan(double x, double y)	{ axis_base = Location(x,y); }
/***********************************/
