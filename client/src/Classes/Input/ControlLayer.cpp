#include "ControlLayer.h"

bool ControlLayer::init()
{
    if (!Layer::init())
        return false;
    
    _controlledPlayer1 = NULL;
    _controlledPlayer2 = NULL;
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
    if (_controlledPlayer1 == NULL)
        return;

    // player 1
    int speed = _controlledPlayer1->getSpeed();
    Point pos = _controlledPlayer1->getPosition();
    Point velocity;

    for (GameController *controller : _enabledControllers)
    {
        if (!controller->isEnabled())
            continue;

        velocity = controller->getPlayer1Velocity();

        if (velocity.x == 0.0 && velocity.y == 0.0)
            continue;

        _controlledPlayer1->setNextPositionDelta(
            ccp(
                velocity.x*dt*speed,
                velocity.y*dt*speed
            )
        );               

        _controlledPlayer1->setNextPosition(
            ccpAdd(pos, _controlledPlayer1->getNextPositionDelta())
        );   
    }

    if (_controlledPlayer2 == NULL)
        return;

    // player 2
    speed = _controlledPlayer2->getSpeed();
    pos = _controlledPlayer2->getPosition();

    for (GameController *controller : _enabledControllers)
    {
        if (!controller->isEnabled())
            continue;

        velocity = controller->getPlayer2Velocity();

        if (velocity.x == 0.0 && velocity.y == 0.0)
            continue;

        _controlledPlayer2->setNextPositionDelta(
            ccp(
                velocity.x*dt*speed,
                velocity.y*dt*speed
            )
        );               

        _controlledPlayer2->setNextPosition(
            ccpAdd(pos, _controlledPlayer2->getNextPositionDelta())
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

void ControlLayer::setControlledPlayer1(Human *sprite)
{
    _player1ActionDelegate = sprite;
    _controlledPlayer1 = sprite;

    for (GameController *controller : _enabledControllers)
    {
        controller->setPlayer1ActionDelegate(sprite);
    }
}

void ControlLayer::setControlledPlayer2(Human *sprite)
{
    _player2ActionDelegate = sprite;
    _controlledPlayer2 = sprite;

    for (GameController *controller : _enabledControllers)
    {
        controller->setPlayer2ActionDelegate(sprite);
    }
}