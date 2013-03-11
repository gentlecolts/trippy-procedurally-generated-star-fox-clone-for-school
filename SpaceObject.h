#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H


class SpaceObject
{
    public:
        SpaceObject();
        virtual void render();
        void update();
        virtual ~SpaceObject();

        double xPos,yPos;
    protected:
        float* model;
        int modelSize;
    private:
};

#endif // SPACEOBJECT_H
