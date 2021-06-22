
#ifndef GAMEOBJ_H_
#define GAMEOBJ_H_
#include "Location.h"
#include "Direction.h"
/******************************/
class Boat;
class Port;
/******************************/
class gameObj	{
    bool update_ready;
public:
    gameObj();
    virtual ~gameObj()	{};
    virtual void update() = 0;
};
/******************************/
#endif
