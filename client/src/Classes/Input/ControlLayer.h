#ifndef __BOMBER_CONTROL_LAYER
#define __BOMBER_CONTROL_LAYER

#include "cocos2d.h"
#include "Touch/Joystick.h"
#include "Keyboard/Keyboard.h"
#include "../Frontend/Sprites/Human.h"
#include "ActionDelegates.h"

using namespace cocos2d;

class ControlLayer: public Layer, ActionDispatcher
{
    public:

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

        void addGameController(GameController* controller);
        void setPauseGameDelegate(PauseGameDelegate *delegate);
        
        void setControlledPlayer1(Human *sprite);
        void setControlledPlayer2(Human *sprite);

    private:
        bool _enabled;

        Joystick *_joystick;
        Keyboard *_keyboard;

        PauseGameDelegate* _pauseGameDelegate;

        std::vector<GameController *> _enabledControllers;
        
        GameSprite * _controlledPlayer1;
        GameSprite * _controlledPlayer2;

};

#endif
