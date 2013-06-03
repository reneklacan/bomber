#include "Human.h"

Human::Human()
{

}

/*
Human::~Human()
{

}
*/

Human* Human::create(Map *map)
{
    Human* sprite = new Human();

    if (sprite && sprite->initWithFile("tiles/timmy.png"))
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

void Human::plantBomb()
{
    _map->spawnBomb(this);
}
