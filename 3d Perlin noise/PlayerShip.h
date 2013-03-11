#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "SpaceObject.h"


class PlayerShip
{
    public:
        PlayerShip();
        virtual ~PlayerShip();
        void render();
    protected:
    private:
        int modelSize;
};

#endif // PLAYERSHIP_H
