#ifndef PLAYERSHIP_H_INCLUDED
#define PLAYERSHIP_H_INCLUDED

#include "gameObject.h"
#include "gameShip.h"

class PlayerShip : public GameShip
{
public:
	void update(double dt);
	PlayerShip(int n);
	void init();
	void uniqueRenderAfterPop();
	void handleKeyInput(double dt);
	void afterSetup();
	void doFire();
protected:
private:
};

#endif // PLAYERSHIP_H_INCLUDED
