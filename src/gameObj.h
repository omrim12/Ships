#ifndef GAMEOBJ_H_
#define GAMEOBJ_H_
/******************************/
class gameObj	{
    bool update_ready;
public:
    gameObj();
    virtual ~gameObj() = 0;
    virtual void update() = 0;
};
/******************************/
#endif

