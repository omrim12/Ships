#include <iostream>
#include "model_main.cpp"
#include "view_main.cpp"
#include "controller_main.cpp"

using namespace std;
/*************************/
//TODO: to be implemented/fixed:

// -----GENERALL-----
//1.	write descriptions for all functions.
//2.	write README file including all assumptions / implementations details
//		that needs to be raised.
//3.	run tests for all class functions.

// -----MODEL-----
//1.	finish port class (including operator == )
//2.	implement create at Model.cpp
//3.	move through _todo's to see if any assignements left behind

// -----VIEW-----
//1.	fix column and row display to match map size.
//2.	fix boat location display (not accurate by map display).

// -----CONTROLLER-----
//1.	run tests for terminal

/*************************/
int main(int argc, char **argv) {

	if( argc < 2 )	{
		cerr << "ERROR: no input file was given.";
		exit(1);
	}

	Controller simulation_control;
	simulation_control.load_data(argv[1]);

    return 0;
}
