#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "SpaceObject.h"


class PlayerShip : public SpaceObject
{
    public:
        PlayerShip();
        virtual ~PlayerShip();
        void render();
    protected:
    private:
};

#endif // PLAYERSHIP_H
