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
CCMenu *GameButton::getGameButton()
{
    return _button;
}

//
void GameButton::setButtonPosition(CCPoint *position)
{
    _position = position;
    _button->setPosition(*_position);
}

//
CCPoint *GameButton::getButtonPosition()
{
    return _position;
}