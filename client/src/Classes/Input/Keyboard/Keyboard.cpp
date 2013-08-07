#include "Keyboard.h"
#include "../../Configuration.h"
#include "../../Frontend/Primitives/MenuHelper.h"

using namespace Bomber::Intern;

Keyboard::Keyboard()
: _player1UpKeyPressed(false)
, _player1DownKeyPressed(false)
, _player1LeftKeyPressed(false)
, _player1RightKeyPressed(false)
, _player2UpKeyPressed(false)
, _player2DownKeyPressed(false)
, _player2LeftKeyPressed(false)
, _player2RightKeyPressed(false)
{

}

bool Keyboard::init()
{
    if (!Layer::init())
        return false;

#ifndef ANDROID
    this->setKeyboardEnabled(true);
#endif

    return true;
}

void Keyboard::keyPressed(int keyCode)
{
    BomberConfiguration *configuration = BomberConfiguration::getInstance();
    
    // player 1 keys
    if (keyCode == configuration->kbPlayer1UpKey || keyCode == configuration->kbPlayer1UpKeyAlt)
    {
        _player1UpKeyPressed = true;
    }
    if (keyCode == configuration->kbPlayer1DownKey || keyCode == configuration->kbPlayer1DownKeyAlt)
    {
        _player1DownKeyPressed = true;
    }
    if (keyCode == configuration->kbPlayer1LeftKey || keyCode == configuration->kbPlayer1LeftKeyAlt)
    {
        _player1LeftKeyPressed = true;
    }
    if (keyCode == configuration->kbPlayer1RightKey || keyCode == configuration->kbPlayer1RightKeyAlt)
    {
        _player1RightKeyPressed = true;
    }
    if (keyCode == configuration->kbPlayer1BombKey || keyCode == configuration->kbPlayer1BombKeyAlt)
    {
        _player1ActionDelegate->actionOne();
    }

    // player 2 keys
    if(Bomber::Frontend::MenuSelections::getInstance()->getNumPlayers() >= 2)
    {
        if (keyCode == configuration->kbPlayer2UpKey || keyCode == configuration->kbPlayer2UpKeyAlt)
        {
            _player2UpKeyPressed = true;
        }
        if (keyCode == configuration->kbPlayer2DownKey || keyCode == configuration->kbPlayer2DownKeyAlt)
        {
            _player2DownKeyPressed = true;
        }
        if (keyCode == configuration->kbPlayer2LeftKey || keyCode == configuration->kbPlayer2LeftKeyAlt)
        {
            _player2LeftKeyPressed = true;
        }
        if (keyCode == configuration->kbPlayer2RightKey || keyCode == configuration->kbPlayer2RightKeyAlt)
        {
            _player2RightKeyPressed = true;
        }
        if (keyCode == configuration->kbPlayer2BombKey || keyCode == configuration->kbPlayer2BombKeyAlt)
        {
            _player2ActionDelegate->actionOne();
        }
    }

    this->updateVelocity();
}

void Keyboard::keyReleased(int keyCode)
{
    BomberConfiguration *configuration = BomberConfiguration::getInstance();
    
    // player 1 keys
    if (keyCode == configuration->kbPlayer1UpKey)
    {
        _player1UpKeyPressed = false;
    }
    if (keyCode == configuration->kbPlayer1DownKey)
    {
        _player1DownKeyPressed = false;
    }
    if (keyCode == configuration->kbPlayer1LeftKey)
    {
        _player1LeftKeyPressed = false;
    }
    if (keyCode == configuration->kbPlayer1RightKey)
    {
        _player1RightKeyPressed = false;
    }

    // player 2 keys
    if(Bomber::Frontend::MenuSelections::getInstance()->getNumPlayers() >= 2)
    {
        if (keyCode == configuration->kbPlayer2UpKey)
        {
            _player2UpKeyPressed = false;
        }
        if (keyCode == configuration->kbPlayer2DownKey)
        {
            _player2DownKeyPressed = false;
        }
        if (keyCode == configuration->kbPlayer2LeftKey)
        {
            _player2LeftKeyPressed = false;
        }
        if (keyCode == configuration->kbPlayer2RightKey)
        {
            _player2RightKeyPressed = false;
        }
    }
    
    if (keyCode == KEY_Escape)
    {
        if (_pauseGameDelegate)
        {
            _pauseGameDelegate->pauseGameAction();
        }
    }

    this->updateVelocity();
}

void Keyboard::updateVelocity()
{
    // player 1
    _player1Velocity = ccp(0, 0);

    if (_player1UpKeyPressed)
    {
        _player1Velocity.y = 1;
    }
    if (_player1DownKeyPressed)
    {
        _player1Velocity.y = _player1Velocity.y - 1;
    }
    if (_player1LeftKeyPressed)
    {
        _player1Velocity.x = -1;
    }
    if (_player1RightKeyPressed)
    {
        _player1Velocity.x = _player1Velocity.x + 1;
    }

    if (_player1Velocity.x && _player1Velocity.y)
    {
        _player1Velocity.x = 0.7 * _player1Velocity.x;
        _player1Velocity.y = 0.7 * _player1Velocity.y;
    }

    // player 2
    if(Bomber::Frontend::MenuSelections::getInstance()->getNumPlayers() >= 2)
    {
        _player2Velocity = ccp(0, 0);

        if (_player2UpKeyPressed)
        {
            _player2Velocity.y = 1;
        }
        if (_player2DownKeyPressed)
        {
            _player2Velocity.y = _player2Velocity.y - 1;
        }
        if (_player2LeftKeyPressed)
        {
            _player2Velocity.x = -1;
        }
        if (_player2RightKeyPressed)
        {
            _player2Velocity.x = _player2Velocity.x + 1;
        }

        if (_player2Velocity.x && _player2Velocity.y)
        {
            _player2Velocity.x = 0.7 * _player2Velocity.x;
            _player2Velocity.y = 0.7 * _player2Velocity.y;
        }
    }
}
