#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_
#include "FileParser.h"
#include "../Model/Model.h"
#include "../View/View.h"
/**********************************/
class Terminal;
/**********************************/
class Controller	{ // This class represents this simulation's controller component.
					  // it's object responsibilty is to parse and validate input commands and
					  // data given from user input while providing data to user regarding the simulations
					  // statuses using Model's interface and the view's graphic outputs.

	Terminal terminal;

public:
	/* exceptions */


	/* c'tors & d'tors */
	Controller():terminal(Terminal())	{}
	~Controller()	{}

	/* class functions */
	void load_data(const char * filename);
	void run();

};
/**********************************/
#endif
