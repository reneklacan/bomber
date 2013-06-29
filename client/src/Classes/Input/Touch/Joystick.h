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
    CCPoint _kCenter;
    CCSprite *_thumb;
    bool _isPressed;

    void updateVelocity(CCPoint point);
    void resetJoystick();
    bool handleLastTouch();
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};

#endif
