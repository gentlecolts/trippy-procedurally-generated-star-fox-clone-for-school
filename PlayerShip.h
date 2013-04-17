#ifndef PLAYERSHIP_H_INCLUDED
#define PLAYERSHIP_H_INCLUDED

#include "gameObject.h"

class PlayerShip : public GameObject
{
public:
	void update(double dt);
	PlayerShip(int n);
	void init();
	void uniqueRenderAfterPop();
	void handleKeyInput(double dt);
protected:
private:
};

#endif // PLAYERSHIP_H_INCLUDED
