#ifndef __BOMBER_JOYSTICK
#define __BOMBER_JOYSTICK

#include "cocos2d.h" 
#include "../GameController.h" 

using namespace cocos2d;

class Joystick : public GameController
{
public:
    CREATE_FUNC(Joystick);
    bool init();
    virtual const char *getName() { return "Touch"; };

private:
    Point _kCenter;
    Sprite *_thumb;
    bool _isPressed;

    void updateVelocity(Point point);
    void resetJoystick();
    bool handleLastTouch();
    void ccTouchesBegan(Set *pTouches, Event *pEvent);
    void ccTouchesMoved(Set *pTouches, Event *pEvent);
    void ccTouchCancelled(Touch *pTouch, Event *pEvent);
    void ccTouchesEnded(Set *pTouches, Event *pEvent);
};

#endif

