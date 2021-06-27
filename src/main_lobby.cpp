#include <process.h>
#include <iostream>

#include "../Controller/controller_main.cpp"
#include "../Model/model_main.cpp"
#include "../View/view_main.cpp"

using namespace std;
/*************************/
//TODO: to be implemented/fixed:

// -----MODEL-----
//1.	fix Boat class deduction via Controller/terminal.cpp .
//2.	check
//3.	add exceptions to Boat, freigther, patrol, cruiser and port.

// -----VIEW-----


// -----CONTROLLER-----

/*************************/
int main(int argc, char **argv) {

	if( argc < 2 )	{
		cerr << "ERROR: no input file was given.";
		exit(1);
	}

	controller_main(argc,argv);
    model_main();
    view_main();


    return 0;
}
