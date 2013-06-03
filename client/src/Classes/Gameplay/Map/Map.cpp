#include "Map.h"
#include "Bomb.h"
#include "../../Constants.h"

Map::Map()
{
    _bombs = new CCArray();
    this->schedule(schedule_selector(Map::update));
}

void Map::update(float dt)
{
    CCObject *it = NULL;
    CCArray *detonatedBombs = new CCArray();

    CCARRAY_FOREACH(_bombs, it)
    {
        Bomb *bomb = (Bomb *) it;
        if (bomb->isDetonated())
        {
            detonatedBombs->addObject(bomb);
        }
    }

    CCARRAY_FOREACH(detonatedBombs, it)
    {
        Bomb *bomb = (Bomb *) it;

        _bombs->fastRemoveObject(bomb);
        this->removeChild(bomb);
        //bomb->release(); // or return to cache
    }
}

void Map::spawnBomb(GameSprite *owner)
{
    printf("spawn bomb on map\n");
    
    CCPoint ownerPos = owner->getPosition();
    CCSize ownerSize = owner->getContentSize();

    int coordX = (int) (ownerPos.x - ownerSize.width/2 + 35.5f)/TILE_WIDTH;
    int coordY = (int) (ownerPos.y - ownerSize.height/2 + 95.5f - TILE_HEIGHT)/TILE_HEIGHT;

	//CCLog("++++++++coords  x:%d, y:%d", coordX, coordY);

    CCPoint origin = ccpAdd(ccp(coordX * 101 + 50.5f, coordY*81 + 50.5f), ccp(0, 0));

    Bomb *bomb = Bomb::create(this, owner);
    bomb->setPosition(origin);
    bomb->setPower(3);
    bomb->setTimeout(2.0f);
}
