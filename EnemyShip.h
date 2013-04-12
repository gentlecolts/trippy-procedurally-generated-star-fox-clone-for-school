#ifndef ENEMYSHIP_H_INCLUDED
#define ENEMYSHIP_H_INCLUDED

#include "gameObject.h"

class EnemyShip : public GameObject
{
public:
	EnemyShip(int n);
    EnemyShip(double x,double y,int n);
    virtual void init(double x,double y);
	virtual void update();
    virtual bool isDone();
    
    void uniqueRender();
protected:
private:
    int t;
};

#endif // ENEMYSHIP_H_INCLUDED
