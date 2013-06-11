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
    _tiledMap = CCTMXTiledMap::create("tiles/level_name.tmx");
    _portalExits = CCDictionary::create();

    this->addChild(_tiledMap, 0, 7);

    _tiledMap->setPosition(ccp(0, 0));

    this->schedule(schedule_selector(Map::updateBombs));

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

    CCSize mapSize = _tiledMap->getMapSize();
    _width = (int) mapSize.width;
    _height = (int) mapSize.height;

    CCTMXLayer *obstaclesLayer = _tiledMap->layerNamed("obstacles");

    _obstaclesMap = (int *) malloc(_width*_height*sizeof(int));

    for (int iy = 0; iy < _height; iy++)
    {
        for (int ix = 0; ix < _width; ix++)
        {
            _obstaclesMap[iy*_width + ix] = obstaclesLayer->tileGIDAt(ccp(ix, _height - 1 - iy));
        }
    }

    return true;
}

void Map::updateBombs(float dt)
{
    CCObject *it = NULL;
    CCArray *detonatedBombs = new CCArray();

    CCARRAY_FOREACH(_bombs, it)
    {
        Bomb *bomb = (Bomb *) it;
        //bomb->updateTimer(dt);
        if (bomb->isDetonated())
        {
            detonatedBombs->addObject(bomb);
        }
    }

    int power, ix, iy, penetration;
    int penetrationTop, penetrationBottom, penetrationLeft, penetrationRight;
    CCPoint epicentrum;

    CCTMXLayer *obstaclesLayer = _tiledMap->layerNamed("obstacles");

    CCARRAY_FOREACH(detonatedBombs, it)
    {
        printf("boooming...\n");
        Bomb *bomb = (Bomb *) it;

        power = bomb->getPower();
        epicentrum = bomb->getTilemapPosition();
        penetration = bomb->getPenetration();

        penetrationTop = penetration;
        penetrationBottom = penetration;
        penetrationLeft = penetration;
        penetrationRight = penetration;

        ix = epicentrum.x;
        iy = epicentrum.y;

        _obstaclesMap[iy*_width + ix] = 0;

        for (int i = 0; i < power; i++)
        {
            ix = epicentrum.x;
            iy = epicentrum.y + i + 1;
            if (_obstaclesMap[iy*_width + ix] == 42 && penetrationTop)
            {
                penetrationTop--;
                obstaclesLayer->removeTileAt(ccp(ix, _height - 1 - iy));
                _obstaclesMap[iy*_width + ix] = 0;
            }

            iy = epicentrum.y - i - 1;
            if (_obstaclesMap[iy*_width + ix] == 42 && penetrationBottom)
            {
                penetrationBottom--;
                obstaclesLayer->removeTileAt(ccp(ix, _height - 1 - iy));
                _obstaclesMap[iy*_width + ix] = 0;
            }

            ix = epicentrum.x + i + 1;
            iy = epicentrum.y;
            if (_obstaclesMap[iy*_width + ix] == 42 && penetrationRight)
            {
                penetrationRight--;
                obstaclesLayer->removeTileAt(ccp(ix, _height - 1 - iy));
                _obstaclesMap[iy*_width + ix] = 0;
            }

            ix = epicentrum.x - i - 1;
            if (_obstaclesMap[iy*_width + ix] == 42 && penetrationLeft)
            {
                penetrationLeft--;
                obstaclesLayer->removeTileAt(ccp(ix, _height - 1 - iy));
                _obstaclesMap[iy*_width + ix] = 0;
            }
        }

        _bombs->fastRemoveObject(bomb);
        this->removeChild(bomb);
        //bomb->release(); // or return to cache
    }
}

void Map::spawnBomb(GameSprite *owner)
{
    CCPoint ownerPos = owner->getPosition();
    CCSize ownerSize = owner->getContentSize();
    CCPoint tilemapPosition = owner->getTilemapPosition(); 

    int ix = (int) tilemapPosition.x;
    int iy = (int) tilemapPosition.y;

    if (_obstaclesMap[iy*_width + ix] != 0)
    {
        return;
    }

    _obstaclesMap[iy*_width + ix] = 777;

    printf("spawn bomb on map at x:%d, y:%d\n", ix, iy);

    CCPoint origin = ccp(ix*101 + 50.5f, iy*81 + 50.5f);

    Bomb *bomb = Bomb::create(this, owner);
    bomb->setPosition(origin);
    bomb->setTilemapPosition(ccp(ix, iy));
    bomb->setPower(3);
    bomb->setTimeout(2.0f);

    _bombs->addObject(bomb);
}

void Map::addToPosition(CCPoint point)
{
    this->setPosition(ccpAdd(this->getPosition(), point));
}
