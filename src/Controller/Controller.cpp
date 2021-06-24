#include "Controller.h"
#include "Terminal.h"
/***************************/
void Controller::load_data(const char * filename)	{
	try	{
		FileParser file_parser = FileParser(filename); // this call generates all port's at Model component.
	}
	catch( exception& e )	{ cerr << e.what() << endl; }
}
/***************************/
void Controller::run()	{ terminal.run(); }
/***************************/
