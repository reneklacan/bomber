#ifndef __BOMBER_ACTION_SPRITE
#define __BOMBER_ACTION_SPRITE

#include "cocos2d.h"
#include "../../Constants.h"

#define STEP_CHANGE_RATE 15
#define MAX_CHANGE_RATE 5
#define MIN_CHANGE_RATE 25

using namespace cocos2d;

class ActionSprite : public Sprite
{
    public:
        ActionSprite(Texture2D *texture, Rect defaultImage);
        void updatePosition(Point newPosition);
        void updateDefaultImage(Rect newImage);
        void spawnPosition(Point spawnPosition);
        void changeRotation(Point pNew);
        void resetRotations();

    protected:
        CC_SYNTHESIZE(int, _speed, Speed);
        CC_SYNTHESIZE(Point, _nextPosition, NextPosition);
        CC_SYNTHESIZE(Point, _nextPositionDelta, NextPositionDelta);
        CC_SYNTHESIZE(unsigned int, _id, ID);
        CC_SYNTHESIZE(bool, _isAlive, IsAlive);

    private:
        Point _position;
        unsigned short _step;   // values 0,1,2 -> transformed to -1,0,1
        Rect _defaultImage;
        unsigned int _counter;
        int _stepImage;
        bool _upHill;            // ascending change of steps
};

#endif