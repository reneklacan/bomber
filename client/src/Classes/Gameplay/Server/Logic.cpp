/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Logic
 */

 #include "Logic.h"
 #include "../Comm/Sockets.h"

//
void Logic::init()
{
    try
    {
        boost::asio::io_service io_service;
        tcp_server server(io_service, this);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    initGame(DEFAULT);
}

//
void Logic::initGame(GAME_LEVELS gameID)
{
    _playersPositions.clear();
    _bombsPositions.clear();

    _playersPositions[58585] = ccp(0, 0); // TODO
    // _obstacles = ???;
    return;
}


//
void Logic::updateState(std::vector<unsigned char> data)
{
    if(data.size() != SEND_PAKET_LENGTH) {
        std::cerr << "Wrong length of received packet: " << data.size() << std::endl;
        return;
    }

    unsigned int sessioID = data[0] * 256 + data[1];
    unsigned int playerID = data[2] * 256 + data[3];
    unsigned int packetType = data[4];
    unsigned int locationX = data[5] * 256 + data[6];
    unsigned int locationY = data[7] * 256 + data[8];

    // DEBUG
    std::cout << "SID: " << sessioID << std::endl << "PID: " << playerID << std::endl << "T: " << 
        packetType << std::endl << "X: " << locationX << std::endl << "Y: " << locationY << std::endl;

    // Movement
    if(packetType == MOVE)
    {
        processMovement(playerID, locationX, locationY);
    }

    return;
}

//
void Logic::processMovement(unsigned int pid, unsigned int p_x, unsigned int p_y)
{/*
    CCObject* co = NULL;
    int x, y, width, height;
    CCRect objRect;
    bool collisionOccured = false;
    bool collisionOccuredX = false;
    bool collisionOccuredY = false;
    CCTMXObjectGroup *objectGroup;
    CCArray *objectList;
    CCDictionary *dict;

    //CCPoint currentPos = _player->getPosition();
    CCPoint nextPos = ccp(p_x, p_y);
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

    if (move)
    {
        // Only send data when something has changed
        if(currentPos.x != nextPos.x || currentPos.y != nextPos.y) 
        {
            // Send Data
            Communication comm = Communication();
            comm.sendSpriteMovement(58585, nextPos.x, nextPos.y);
        }

        _player->setPosition(nextPos);
        _map->addToPosition(ccpSub(currentPos, nextPos));
    }

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
    {*/
        /*
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
    }
*/
}