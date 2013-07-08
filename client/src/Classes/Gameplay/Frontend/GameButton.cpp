#include "GameButton.h"

using namespace Bomber::Frontend;

//
unsigned int GameButton::getWidth()
{
    return _width;
}

//
unsigned int GameButton::getHeight()
{
    return _height;
}

//
Node *GameButton::getGameButton()
{
    return _button;
}

//
void GameButton::setButtonPosition(Point *position)
{
    _position = position;
    _button->setPosition(*_position);
}

//
Point *GameButton::getButtonPosition()
{
    return _position;
}