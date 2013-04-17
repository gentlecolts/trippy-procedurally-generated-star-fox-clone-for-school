#ifndef ENEMYSHIP_H_INCLUDED
#define ENEMYSHIP_H_INCLUDED

#include "gameObject.h"

class EnemyShip : public GameObject
{
public:
	EnemyShip(int n);
    EnemyShip(double x,double y,int n);
    virtual void init(double x,double y);
	virtual void update(double dt);
    virtual bool isDone();
protected:
	bool dead;
    double t;
private:
};

#endif // ENEMYSHIP_H_INCLUDED
