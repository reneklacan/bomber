#include "Map.h"
#include "Bomb.h"
#include "../../Constants.h"

Map::Map()
{
}

Map::~Map()
{
}

bool Map::init()
{
    if (!CCLayer::init())
        return false;

    _bombs = new CCArray();
    _tiledMap = CCTMXTiledMap::create("tiles/kocky.tmx");
    _portalExits = CCDictionary::create();

    this->addChild(_tiledMap, 0, 7);

    _tiledMap->setPosition(ccp(0, 0));

    this->schedule(schedule_selector(Map::update));

    CCTMXObjectGroup *objectGroup = _tiledMap->objectGroupNamed("portal_exits");
    CCArray *objectList = objectGroup->getObjects();

    CCObject* co = NULL;
    CCDictionary *dict = NULL;
    int id;

    CCARRAY_FOREACH(objectList, co)
    {
        dict = (CCDictionary*) co;
        if (!dict)
            break;

        id = ((CCString*) dict->objectForKey("name"))->intValue();
        _portalExits->setObject(co, id);
    }

    return true;
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
