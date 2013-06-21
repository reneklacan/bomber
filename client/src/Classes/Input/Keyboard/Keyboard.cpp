#include "Keyboard.h"

bool Keyboard::init()
{
    if (!CCLayer::init())
        return false;

#ifndef ANDROID
    this->setKeyboardEnabled(true);
#endif

    return true;
}

void Keyboard::keyPressed(int keyCode)
{
    switch (keyCode)
    {
        case KEY_W:
        case KEY_ArrowUp:
            _upArrowPressed = true;
            break;

        case KEY_D:
        case KEY_ArrowRight:
            _rightArrowPressed = true;
            break;

        case KEY_S:
        case KEY_ArrowDown:
            _downArrowPressed = true;
            break;

        case KEY_A:
        case KEY_ArrowLeft:
            _leftArrowPressed = true;
            break;

        case KEY_Space:
            _gameActionDelefate->actionOne();
            break;

        default:
            return;
    }

    this->updateVelocity();
}

void Keyboard::keyReleased(int keyCode)
{
    switch (keyCode)
    {
        case KEY_W:
        case KEY_ArrowUp:
            _upArrowPressed = false;
            break;

        case KEY_D:
        case KEY_ArrowRight:
            _rightArrowPressed = false;
            break;

        case KEY_S:
        case KEY_ArrowDown:
            _downArrowPressed = false;
            break;

        case KEY_A:
        case KEY_ArrowLeft:
            _leftArrowPressed = false;
            break;

        case KEY_Space:
            _actionKeyOnePressed = false;
            break;

        case KEY_Escape:
            if (_pauseGameDelegate)
            {
                _pauseGameDelegate->pauseGameAction();
            }
            break;

        default:
            return;
    }

    this->updateVelocity();
}

void Keyboard::updateVelocity()
{
    _velocity = ccp(0, 0);

    if (_upArrowPressed)
    {
        _velocity.y = 1;
    }
    if (_downArrowPressed)
    {
        _velocity.y = _velocity.y - 1;
    }
    if (_leftArrowPressed)
    {
        _velocity.x = -1;
    }
    if (_rightArrowPressed)
    {
        _velocity.x = _velocity.x + 1;
    }

    if (_velocity.x && _velocity.y)
    {
        _velocity.x = 0.7 * _velocity.x;
        _velocity.y = 0.7 * _velocity.y;
    }
}
