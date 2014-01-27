#ifndef __BOMBER_ACTION_SPRITE
#define __BOMBER_ACTION_SPRITE

#include "cocos2d.h"
#include "../../Constants.h"

#define STEP_CHANGE_RATE 15

using namespace cocos2d;

class ActionSprite : public Sprite
{
    public:
        ActionSprite(Texture2D *texture, Rect defaultImage);
        void updatePosition(Point newPosition);
        void updateDefaultImage(Rect newImage);
        void spawnPosition(Point spawnPosition);
        void changeRotation(Point pNew);

    private:
        Point _position;
        unsigned short _step;   // values 0,1,2 -> transformed to -1,0,1
        Rect _defaultImage;
        unsigned int _counter;
        int _stepImage;
        bool _upHill;            // ascending change of steps
};

#endif