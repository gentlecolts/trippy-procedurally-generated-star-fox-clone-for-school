#ifndef PLAYERSHIP_H_INCLUDED
#define PLAYERSHIP_H_INCLUDED

#include "gameObject.h"

class PlayerShip : public GameObject
{
public:
	void update();
	PlayerShip();
	void init();
	void uniqueRenderAfterPop();
	void handleKeyInput();
protected:
private:
};

#endif // PLAYERSHIP_H_INCLUDED
