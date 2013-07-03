#include "ControlLayer.h"

bool ControlLayer::init()
{
    if (!Layer::init())
        return false;

    _keyboard = NULL;
    _joystick = NULL;

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

    Point pos = _controlledSprite->getPosition();
    Point velocity;

    for (GameController *controller : _enabledControllers)
    {
        if (!controller->isEnabled())
            continue;

        velocity = controller->getVelocity();

        if (velocity.x == 0.0 && velocity.y == 0.0)
            continue;

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
}

void ControlLayer::enableJoystick()
{
    if (_joystick == NULL)
    {
        _joystick =  Joystick::create();
        this->addGameController(_joystick);
    }
    _joystick->setEnabled(true);
}

void ControlLayer::disableJoystick()
{
    _joystick->setEnabled(false);
}

void ControlLayer::enableKeyboard()
{
    if (_keyboard == NULL)
    {
        _keyboard = Keyboard::create();
        this->addGameController(_keyboard);
    }
    _keyboard->setEnabled(true);
}

void ControlLayer::addGameController(GameController* controller)
{
    if (_pauseGameDelegate)
    {
        controller->setPauseGameDelegate(_pauseGameDelegate);
    }
    this->addChild(controller, 2);
    _enabledControllers.push_back(controller);
}

void ControlLayer::disableKeyboard()
{
    _keyboard->setEnabled(false);
}

void ControlLayer::enableAccelerometer()
{

}

void ControlLayer::disableAccelerometer()
{

}

void ControlLayer::setPauseGameDelegate(PauseGameDelegate *delegate)
{
    _pauseGameDelegate = delegate;

    for (GameController *controller : _enabledControllers)
    {
        controller->setPauseGameDelegate(delegate);
    }
}

void ControlLayer::setGameActionDelegate(GameActionDelegate *delegate)
{
    _gameActionDelefate = delegate;

    for (GameController *controller : _enabledControllers)
    {
        controller->setGameActionDelegate(delegate);
    }
}
