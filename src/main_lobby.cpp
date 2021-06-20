#include "Model/model_main.h"
#include "View/view_main.h"
#include "Controller/controller_main.h"
using namespace std;
/*************************/
//TODO: to be implemented/fixed:

// -----MODEL-----
//1.	Boat and GameObj destructor defined outside of class. check why doesnt work
//2.	remember: ports update is **after** boats update!
//3.	add exceptions to freigther

// -----VIEW-----


// -----CONTROLLER-----

/*************************/
int main() {

    model_main();
    view_main();
    controller_main();

    return 0;
}
