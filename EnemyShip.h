#ifndef ENEMYSHIP_H_INCLUDED
#define ENEMYSHIP_H_INCLUDED

#include "gameObject.h"

class EnemyShip : public GameObject
{
public:
	void init();
	void update();
protected:
private:
    int t;
};

#endif // ENEMYSHIP_H_INCLUDED
