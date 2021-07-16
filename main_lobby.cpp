#include <iostream>
#include "Controller/Controller.h"
#include "Model/Model.h"
#include "View/View.h"
using namespace std;
/*************************/
//TODO: to be implemented/fixed:

// -----GENERALL-----
//1.	write descriptions for all functions.
//2.	write README file including all assumptions / implementations details
//		that needs to be raised.
//3.	run tests for all class functions.

// -----MODEL-----
//1.	move through _todo's to see if any assignements left behind
//2.	problems with operator == (where is it calling errors from ???)

// -----VIEW-----
//1.	fix column and row display to match map size.
//2.	fix boat location display (not accurate by map display).

// -----CONTROLLER-----
//1.	run tests for terminal
//2.	FileParser raises problem with calling Port's different c'tors.
/*************************/

int main(int argc, char const *argv[])
{
	cout << "hiush!" << endl;

	if (argc < 2)
	{
		cerr << "ERROR: no input file was given.";
		exit(1);
	}

	Controller simulation_control;
	simulation_control.load_data(argv[1]);
	simulation_control.run();

	return 0;
}
