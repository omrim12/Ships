#include "Controller.h"

/******************************/
void controller_main(int argc, char **argv)	{
	Controller control;
	control.load_data(argv[1]);
	control.run();
}
