#include "Human.h"
#include "../../Backend/Mediator.h"

using namespace Bomber;

Human::Human()
{

}

/*
Human::~Human()
{

}
*/

Human* Human::create(Map *map, int type)
{
    Human* sprite = new Human();

    if(sprite)
    {
        sprite->autorelease();
        return sprite; 
    }

    CC_SAFE_DELETE(sprite);
    return NULL;
}

void Human::actionOne()
{
    this->plantBomb();
}

void Human::actionTwo()
{

}

void Human::actionThree()
{

}

void Human::plantBomb()
{
    //_map->spawnBomb(this);
    Backend::Mediator::getInstance()->spawnBomb();
}
