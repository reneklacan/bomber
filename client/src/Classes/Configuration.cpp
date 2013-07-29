
#include "Configuration.h"

using namespace Bomber::Intern;

BomberConfiguration *BomberConfiguration::_instance = NULL;

BomberConfiguration* BomberConfiguration::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new BomberConfiguration();
    }
    return _instance;
}

BomberConfiguration::BomberConfiguration()
{
    kbPlayer1UpKey = KEY_W;
    kbPlayer1DownKey = KEY_S;
    kbPlayer1LeftKey = KEY_A;
    kbPlayer1RightKey = KEY_D;
    kbPlayer1BombKey = KEY_Space;
    
    kbPlayer1UpKeyAlt = -1;
    kbPlayer1DownKeyAlt = -1;
    kbPlayer1LeftKeyAlt = -1;
    kbPlayer1RightKeyAlt = -1;
    kbPlayer1BombKeyAlt = -1;
    
    kbPlayer2UpKey = KEY_ArrowUp;
    kbPlayer2DownKey = KEY_ArrowDown;
    kbPlayer2LeftKey = KEY_ArrowLeft;
    kbPlayer2RightKey = KEY_ArrowRight;
    kbPlayer2BombKey = KEY_NumPad0;
    
    kbPlayer2UpKeyAlt = -1;
    kbPlayer2DownKeyAlt = -1;
    kbPlayer2LeftKeyAlt = -1;
    kbPlayer2RightKeyAlt = -1;
    kbPlayer2BombKeyAlt = -1;
}