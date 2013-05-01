#ifndef ENEMYSHIP_H_INCLUDED
#define ENEMYSHIP_H_INCLUDED

#include "GameObject.h"
#include "gameShip.h"

class EnemyShip : public GameShip
{
public:
	EnemyShip(int n);
    EnemyShip(double x,double y,int n);
    virtual void init(double x,double y);
	virtual void update(double dt);
    virtual bool isDone();
protected:
	bool dead;
private:
};

#endif // ENEMYSHIP_H_INCLUDED
