
#include "Joystick.h" 

#define JOYSTICK_OFFSET_X 15.0f
#define JOYSTICK_OFFSET_Y 15.0f

#define JOYSTICK_RADIUS 64.0f

#define THUMB_RADIUS 26.0f

static CCPoint convertCoordinate(CCPoint point)
{
    return CCDirector::sharedDirector()->convertToGL(point);
}

static bool isPointInCircle(CCPoint point, CCPoint center, float radius)
{
    float dx = (point.x - center.x);
    float dy = (point.y - center.y);
    return (radius >= sqrt((dx*dx)+(dy*dy)));
}

bool Joystick::init()
{
    _kCenter=CCPoint(JOYSTICK_RADIUS + JOYSTICK_OFFSET_X, JOYSTICK_RADIUS + JOYSTICK_OFFSET_Y);

    if (!CCLayer::init())
        return false;

    this->setTouchEnabled(true);
    _velocity = CCPointZero;

    CCSprite *bg = CCSprite::create("joystick_background.png");
    bg->setPosition(_kCenter);
    this->addChild(bg, 0);

    _thumb = CCSprite::create("joystick_thumb.png");
    _thumb->setPosition(_kCenter);
    this->addChild(_thumb, 1);

    return true;
}

void Joystick::updateVelocity(CCPoint point)
{
    // calculate Angle and length
    float dx = point.x - _kCenter.x;
    float dy = point.y - _kCenter.y;

    float distance = sqrt(dx*dx + dy*dy);
    float angle = atan2(dy,dx); // in radians

    if (distance > JOYSTICK_RADIUS)
    {
        dx = cos(angle) * JOYSTICK_RADIUS;
        dy = sin(angle) * JOYSTICK_RADIUS;
    }

    _velocity = CCPointMake(dx/JOYSTICK_RADIUS, dy/JOYSTICK_RADIUS);

    if (distance > THUMB_RADIUS)
    {
        point.x = _kCenter.x + cos(angle) * THUMB_RADIUS;
        point.y = _kCenter.y + sin(angle) * THUMB_RADIUS;
    }

    _thumb->setPosition(point);
}

void Joystick::resetJoystick()
{
    this->updateVelocity(_kCenter);
}

bool Joystick::handleLastTouch()
{
    bool wasPressed = _isPressed;
    if (wasPressed)
    {
        this->resetJoystick();
        _isPressed = false;
    }
    return (wasPressed ? true : false);
}

void Joystick::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint point = touch->getLocationInView();
    point = convertCoordinate(point);

    if (isPointInCircle(point, _kCenter, JOYSTICK_RADIUS))
    {
        _isPressed = true;
        this->updateVelocity(point);
    }
}

void Joystick::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (_isPressed)
    {
        CCTouch *touch = (CCTouch*)pTouches->anyObject();
        CCPoint point = touch->getLocationInView();
        point = convertCoordinate(point);
        this->updateVelocity(point);
    }
}

void Joystick::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    this->handleLastTouch();
}

void Joystick::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    this->handleLastTouch();
}
