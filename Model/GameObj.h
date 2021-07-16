
#ifndef GAMEOBJ_H_
#define GAMEOBJ_H_
#include "Location.h"
#include "Direction.h"
/******************************/
class Boat;
class Port;
/******************************/
class GameObj
{
	bool update_ready;

public:
	GameObj();
	virtual ~GameObj(){};
	virtual void update() = 0;
};
/******************************/
#endif
