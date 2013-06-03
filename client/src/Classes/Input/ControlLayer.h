#ifndef __BOMBER_CONTROL_LAYER
#define __BOMBER_CONTROL_LAYER

#include "cocos2d.h"
#include "Joystick.h"
#include "Keyboard.h"
#include "../Gameplay/Sprites/GameSprite.h"

using namespace cocos2d;

class ControlLayer: public CCLayer
{
    public:
        CC_SYNTHESIZE(GameSprite *, _controlledSprite, ControlledSprite);

        //ControlLayer();
        //~ControlLayer();
        CREATE_FUNC(ControlLayer);

        virtual bool init();

        void enable();
        void disable();

        void update(float dt);
        // joystick stuff
        void enableJoystick();
        void disableJoystick();
        // keyboard stuff
        void enableKeyboard();
        void disableKeyboard();
        // accelerometer stuff
        void enableAccelerometer();
        void disableAccelerometer();

    private:
        bool _enabled;
        bool _joystickEnabled;
        Joystick *_joystick;
        bool _keyboardEnabled;
        Keyboard *_keyboard;
};

#endif
