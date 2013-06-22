#include "LevelLayer.h"
#include "../Constants.h"

LevelLayer::LevelLayer()
:_player(NULL)
,_map(NULL)
{
}

LevelLayer::~LevelLayer()
{
}

bool LevelLayer::init()
{
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);

    if (!CCLayer::init())
        return false;

    _map = Map::create();
    _player = Human::create(_map);
    _controlLayer = ControlLayer::create();

    _player->retain();

    this->addChild(_map);
    this->addChild(_controlLayer, 2);

    _map->addChild(_player, 1);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //_player = (GameSprite *) layer->tileAt(ccp(0, 5));
    //_player = GameSprite::gameSpriteWithFile("tiles/timmy.png");
    //_player->setSpeed(1);
    //_player->setPosition(CC_POINT_PIXELS_TO_POINTS(ccp(mapWidth/2,0)));
    //_player->setAnchorPoint(ccp(0.5f, 0.3f));

    _controlLayer->setControlledSprite((GameSprite *)_player);
    _controlLayer->enableJoystick();
    _controlLayer->enableKeyboard();

    // Start Local Server
    LocalServer& localServer = LocalServer::getInstance();
    localServer.startServer();
    
    _player->setPosition(
            ccp(
                origin.x + _player->getContentSize().width/2 + 101,
                origin.y + visibleSize.height/2
            )
    );
    _map->setPosition(
            ccp(
                visibleSize.width/2 - _player->getPosition().x,
                0
            )
    );

    // use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
    // see http://www.cocos2d-x.org/boards/6/topics/1478
    this->schedule( schedule_selector(LevelLayer::repositionSprite) );
    this->schedule( schedule_selector(LevelLayer::updateGame) );

    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);

	return true;
}

void LevelLayer::repositionSprite(float dt)
{
    CCPoint p = _player->getPosition();
    //p = CC_POINT_POINTS_TO_PIXELS(p);
    int z = -( (p.y+100.5) /81 ) + 0;
    _player->setVertexZ( z );
}

void LevelLayer::updateGame(float dt)
{
    //CCObject* co = NULL;
    //int x, y, width, height;
    CCRect objRect;
    bool collisionOccured = false;
    bool collisionOccuredX = false;
    bool collisionOccuredY = false;
    //CCTMXObjectGroup *objectGroup;
    //CCArray *objectList;
    //CCDictionary *dict;

    CCPoint currentPos = _player->getPosition();
    CCPoint nextPos = _player->getNextPosition();
    CCPoint nextPosX = ccp(nextPos.x, currentPos.y);
    CCPoint nextPosY = ccp(currentPos.x, nextPos.y);

    CCRect playerRect = _player->getCollisionBox();
    CCRect playerRectX = _player->getCollisionBox(nextPosX);
    CCRect playerRectY = _player->getCollisionBox(nextPosY);

    CCTMXLayer *obstaclesLayer = _map->getTiledMap()->layerNamed("obstacles");

    CCPoint tilemapPosition = _player->getTilemapPosition();

    for (int iy = tilemapPosition.y - 1; iy <= tilemapPosition.y + 1; iy++)
    {
        for (int ix = tilemapPosition.x - 1; ix <= tilemapPosition.x + 1; ix++)
        {
            if (!obstaclesLayer->tileGIDAt(ccp(ix, _map->getHeight() - 1 - iy)))
                continue;

            objRect = CCRectMake(ix*TILE_WIDTH, iy*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

            if (!collisionOccured && playerRect.intersectsRect(objRect))
                collisionOccured = true;
            if (!collisionOccuredX && playerRectX.intersectsRect(objRect))
                collisionOccuredX = true;
            if (!collisionOccuredY && playerRectY.intersectsRect(objRect))
                collisionOccuredY = true;
        }
    }

    bool move = true;

    if (!collisionOccured)
        ;
    else if (!collisionOccuredX)
        nextPos = nextPosX;
    else if (!collisionOccuredY)
        nextPos = nextPosY;
    else
        move = false;

    /*if (move)
    {
        // Only send data when something has changed
        if(currentPos.x != nextPos.x || currentPos.y != nextPos.y) 
        {
            // Send Data
            Communication comm = Communication();
            comm.sendSpriteMovement(58585, nextPos.x, nextPos.y);
        }

        //_player->setPosition(nextPos);
        //_map->addToPosition(ccpSub(currentPos, nextPos));
    }*/

    // Get Data
    Communication *comm = Communication::getInstance();
    if(currentPos.x != nextPos.x || currentPos.y != nextPos.y) 
    {
        // Send Data
        comm->sendSpriteMovement(58585, nextPos.x, nextPos.y);
    }
    comm->receiveServerData();

    // Get Player Data
    PlayerInfo *pI = comm->getPlayerInfo(58585);
    CCPoint serverNextPosition;
    if(pI->valid)
    {
       serverNextPosition = ccp(pI->x, pI->y); 
    }
    else
    {
        serverNextPosition = currentPos;
    }
    _player->setPosition(serverNextPosition);
    _map->addToPosition(ccpSub(currentPos, serverNextPosition));

    // PORTALS FROM HERE
/*
    CCPoint mapPos = _map->getPosition();

    collisionOccured = false;

    objectGroup = _map->getTiledMap()->objectGroupNamed("portals");
    objectList = objectGroup->getObjects();

    CCString *name;

    int portalExit = 0;

    // use CCDictionary for portals and portal_exits?

    CCARRAY_FOREACH(objectList, co)
    {
        dict = (CCDictionary*) co;

        if (!dict)
            break;

        name = ((CCString*)dict->objectForKey("name"));
        x = ((CCString*)dict->objectForKey("x"))->intValue();
        y = ((CCString*)dict->objectForKey("y"))->intValue();
        width = ((CCString*)dict->objectForKey("width"))->intValue();
        height = ((CCString*)dict->objectForKey("height"))->intValue();         

        //printf( "x %i, y %i, width %i, height %i\n", x, y, width, height );

        objRect = CCRectMake(
                x, y, width, height
        );
        //printf("obj rect height is %g\n", objRect.size.height);

        if (playerRect.intersectsRect(objRect))
        {
            //_player->setPosition(pos);
            portalExit = name->intValue();
            break;
        }

    }

    if (portalExit)
    {
*/        /*
        dict = (CCDictionary*) _map->getPortalExits()->objectForKey(portalExit);

        if (dict != NULL)
        {
            x = ((CCString*)dict->objectForKey("x"))->intValue();
            y = ((CCString*)dict->objectForKey("y"))->intValue();

            x += 15;
            y += 40;

            std::cout << "teleport!!!! " << portalExit << std::endl;

            CCPoint delta = ccpSub(_player->getPosition(), ccp(x, y));
            _player->setPosition(ccp(x, y));

            CCPoint mapPos = _map->getPosition();
            _map->setPosition(ccpAdd(mapPos, delta));
        }

        return;
        */
/*
        objectGroup = _map->getTiledMap()->objectGroupNamed("portal_exits");
        objectList = objectGroup->getObjects();

        bool found = false;

        CCARRAY_FOREACH(objectList, co)
        {
            dict = (CCDictionary*) co;

            if (!dict)
                break;

            name = ((CCString*)dict->objectForKey("name"));
            x = ((CCString*)dict->objectForKey("x"))->intValue();
            y = ((CCString*)dict->objectForKey("y"))->intValue();

            if (portalExit == name->intValue())
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            x += 15;
            y += 40;

            std::cout << "teleport!!!! " << portalExit << std::endl;

            CCPoint delta = ccpSub(_player->getPosition(), ccp(x, y));
            _player->setPosition(ccp(x, y));

            CCPoint mapPos = _map->getPosition();
            _map->setPosition(
                    ccpAdd(mapPos, delta)
            );
        }
    }*/
}
