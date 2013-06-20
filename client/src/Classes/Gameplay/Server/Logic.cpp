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
    this->initGame(DEFAULT);

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
}

//
void Logic::initGame(GAME_LEVELS gameID)
{
    _playersPositions.clear();
    _bombsPositions.clear();
    _obstacles.clear();
    _portals.clear();
    _items.clear();

    _playersPositions[58585] = new Point(0, 0); // TODO

    // Parse Map
    XMLDocument doc;
    doc.LoadFile("../Resources/tiles/level_name.tmx");
    XMLElement* element = doc.FirstChildElement("map")->FirstChildElement("layer");
    XMLElement* obstaclesLayer = NULL;
    XMLElement* portalsLayer = NULL;
    XMLElement* itemsLayer = NULL;

    /// Obstacles, Portals
    while(element != NULL)
    {
        if( strcmp(element->Attribute("name"), "obstacles") == 0 )
        {
            obstaclesLayer = element;
        }
        else if( strcmp(element->Attribute("name"), "portals") == 0 )
        {
            portalsLayer = element;
        }
        else if( strcmp(element->Attribute("name"), "items") == 0 )
        {
            itemsLayer = element;
        }
        element = element->NextSiblingElement("layer");
    }

    this->initLayer(obstaclesLayer, _obstacles);
    this->initLayer(portalsLayer, _portals);
    this->initLayer(itemsLayer, _items);

    _isReady = true;

    // DEBUG
    /*for(std::map<Point *, GAME_LAYER_OBJECTS>::iterator it = _obstacles.begin(); it != _obstacles.end(); it++)
    {
        std::cout << "Obstacle: [" << it->first->x << ", "<< it->first->y << "] = " << it->second << std::endl;
    }
    for(std::map<Point *, GAME_LAYER_OBJECTS>::iterator it = _portals.begin(); it != _portals.end(); it++)
    {
        std::cout << "Portal: [" << it->first->x << ", "<< it->first->y << "] = " << it->second << std::endl;
    }
    for(std::map<Point *, GAME_LAYER_OBJECTS>::iterator it = _items.begin(); it != _items.end(); it++)
    {
        std::cout << "Items: [" << it->first->x << ", "<< it->first->y << "] = " << it->second << std::endl;
    }*/

    return;
}

//
void Logic::initLayer(XMLElement* element, std::map<Point *, GAME_LAYER_OBJECTS> &structure)
{
    if(element == NULL)
    {
        std::cerr << "Map does not contain one or more necessary layers." << std::endl;
    }

    int coo_count = 0;
    int max_x = element->IntAttribute("width");
    int max_y = element->IntAttribute("height");
    for(XMLElement* obsTile = element->FirstChildElement("data")->FirstChildElement("tile"); 
        obsTile != NULL; obsTile = obsTile->NextSiblingElement())
    {
        // Get coordinates
        int obs_x = coo_count % max_x;
        int obs_y = max_y - (coo_count / max_x) - 1;
        // Save type of obsatecle
        int obs_t = obsTile->IntAttribute("gid");
        if(obs_t != 0)
        {
            structure[new Point(obs_x, obs_y)] = (GAME_LAYER_OBJECTS)obs_t;
        }
        coo_count++;
    }
    return;
}

std::map<unsigned int, Point *> &Logic::getPlayersPositions()
{
    return _playersPositions;
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
        this->processMovement(playerID, locationX, locationY);
    }
    else if(packetType == PLANT)
    {
        this->processPlanting(playerID, locationX, locationY);
    }

    return;
}

//
void Logic::processMovement(unsigned int pid, unsigned int p_x, unsigned int p_y)
{

    _playersPositions[pid]->x = p_x;
    _playersPositions[pid]->y = p_y;

    /*
    CCObject* co = NULL;
    int x, y, width, height;
    CCRect objRect;
    bool collisionOccured = false;
    bool collisionOccuredX = false;
    bool collisionOccuredY = false;
    CCTMXObjectGroup *objectGroup;
    CCArray *objectList;
    CCDictionary *dict;

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

//
void Logic::processPlanting(unsigned int pid, unsigned int p_x, unsigned int p_y)
{
    return;
}