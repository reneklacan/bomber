
#include "Sprite.h"

using namespace Bomber::Backend;

Sprite::Sprite()
: GameObject()
{
    _name = "sprite?";
    _attributes = new SpriteAttributes();
}

Sprite::~Sprite()
{
    delete _attributes;
}

void Sprite::configureFromGid(unsigned int gid)
{

}
