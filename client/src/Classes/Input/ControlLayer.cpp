#include "ControlLayer.h"

bool ControlLayer::init()
{
    if (!CCLayer::init())
        return false;

    this->schedule(schedule_selector(ControlLayer::update));

    return true;
}

/*
ControlLayer::~ControlLayer()
{

}
*/

void ControlLayer::update(float dt)
{
    float sensitivity = 20.0f;
    float speed = _controlledSprite->getSpeed();

    CCPoint pos = _controlledSprite->getPosition();
    CCPoint velocity;

    if (_joystickEnabled)
    {
        velocity = _joystick->getVelocity();
    }

    if (_keyboardEnabled && !velocity.x && !velocity.y)
    {
        velocity = _keyboard->getVelocity();
        if (_keyboard->isActionKeyOnePressed())
        {
            _controlledSprite->actionOne();
        }
    }

    _controlledSprite->setNextPositionDelta(
            ccp(
                velocity.x*sensitivity*dt*speed,
                velocity.y*sensitivity*dt*speed
            )
    );

    _controlledSprite->setNextPosition(
            ccpAdd(pos, _controlledSprite->getNextPositionDelta())
    );
}

void ControlLayer::enableJoystick()
{
    _joystickEnabled = true;
    _joystick =  Joystick::create();
    this->addChild(_joystick, 2);
}

void ControlLayer::disableJoystick()
{

}

void ControlLayer::enableKeyboard()
{
    _keyboardEnabled = true;
    _keyboard = Keyboard::create();
    this->addChild(_keyboard, 2);
    //this->setKeyboardEnabled(true);
}

void ControlLayer::disableKeyboard()
{
    _keyboardEnabled = false;
    //this->setKeyboardEnabled(false);
}

void ControlLayer::enableAccelerometer()
{

}

void ControlLayer::disableAccelerometer()
{

}
