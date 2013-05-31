#include "Human.h"

/*
Human::Human()
{

}

Human::~Human()
{

}
*/

Human* Human::create()
{
    Human* sprite = new Human();

    if (sprite && sprite->initWithFile("tiles/timmy.png"))
    {
        sprite->autorelease();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);
    return NULL;
}
