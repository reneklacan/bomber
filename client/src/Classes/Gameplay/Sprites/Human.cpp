#include "Human.h"
#include "../Backend/Mediator.h"

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

    std::string image;
    if(type == 0)
    {
        image = "tiles/timmy.png";
    }
    else
    {
        image = "tiles/timmy-evil.png";
    }

    if (sprite && sprite->initWithFile(image.c_str()))
    {
        sprite->setMap(map);
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
