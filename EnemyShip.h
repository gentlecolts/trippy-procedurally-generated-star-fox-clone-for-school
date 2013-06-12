#ifndef ENEMYSHIP_H_INCLUDED
#define ENEMYSHIP_H_INCLUDED

#include "GameObject.h"
#include "gameShip.h"

class EnemyShip : public GameShip
{
public:
	virtual char* getType();
	EnemyShip();
    EnemyShip(double x,double y);
    virtual void init(double x,double y, int startPos, int time);
	virtual void update(double dt);
    virtual bool isDone();
protected:
	bool dead;
private:
};

#endif // ENEMYSHIP_H_INCLUDED
