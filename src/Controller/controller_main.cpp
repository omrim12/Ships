#include "Controller.h"
/******************************/
//TODO: run tests for:
//1. file parser (wont see Model).
//2. terminal commands and exception raising (invalid input, invalid content etc.).
/******************************/
void controller_main(int argc, char **argv)	{
	Controller control;
	control.load_data(argv[1]);
	control.run();
}
