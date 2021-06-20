#include "src/Model/model_main.h"
#include "src/View/view_main.h"
#include "src/Controller/controller_main.h"
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
