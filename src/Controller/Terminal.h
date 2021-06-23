#include <iostream>
#include "C:\Users\ex3_ships_simulation\ships_simulation-main\src\Model\Model.h"
#include "C:\Users\ex3_ships_simulation\ships_simulation-main\src\View\View.h"

using namespace std;

class Terminal {
    static int Time;
    View view;
public:
    Terminal() {Time=0;}
    void run();

};

