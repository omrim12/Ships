#ifndef GAMEOBJ_H_
#define GAMEOBJ_H_
/******************************/
class gameObj	{
    bool update_ready;
public:
    gameObj():update_ready(false)	{}
    virtual ~gameObj()	{};
    virtual void update() = 0;
};
/******************************/
#endif

