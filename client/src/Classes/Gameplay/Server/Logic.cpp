/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Logic
 */

#include "Logic.h"
#include "../Comm/Sockets.h"
#include "../Comm/Protocol_v1.h"

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

    _playersPositions[58585] = new Point(150, 486); // TODO

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
std::vector<unsigned char> Logic::getState()
{
    // Get player positions
    //std::map<unsigned int, Point *> &pP = this->getPlayersPositions();
    _buffer.clear();
    _data.players_data.clear();

    // Inicialize data structure
    _data.session_id = 14568; // TODO
    _data.num_players = _playersPositions.size();
    for(std::map<unsigned int, Point *>::iterator it = _playersPositions.begin(); it != _playersPositions.end(); it++)
    {
        TServerPlayer sP = 
        {
            PLAYER_ACTION_PAKET_LENGTH,
            it->first,
            0, // TODO
            it->second->x,
            it->second->y
        };
        std::cout << "Sender: " << "Player (" << it->first << "): " << it->second->x << " " << it->second->y << std::endl;
        _data.players_data.push_back(sP);
    }

    // Create packet
    _protocol->setDataServerSync(_buffer, _data);

    // DEBUG
    //std::cout << "Sender: " << "Player (" << 58585 << "): " << _playersPositions[58585]->x << " " << _playersPositions[58585]->y << std::endl;

    return _buffer;
}

//
void Logic::updateState(std::vector<unsigned char> data)
{
    // Parse data
    TPlayerAction playerAction;
    bool result = _protocol->getDataPlayerAction(&playerAction, data);
    if(!result)
    {
        std::cerr << "Cannot update state." << std::endl;
        return;
    }

    // DEBUG
    /*std::cout << "SID: " << playerAction.session_id << std::endl << "PID: " << playerAction.player_id << std::endl << "T: " << 
        playerAction.action_type << std::endl << "X: " << playerAction.location_x << std::endl << "Y: " << playerAction.location_y << std::endl;*/

    // Movement
    if(playerAction.action_type == MOVE)
    {
        this->processMovement(playerAction.player_id, playerAction.location_x, playerAction.location_y);
    }
    // Bomb
    else if(playerAction.action_type == PLANT)
    {
        this->processPlanting(playerAction.player_id, playerAction.location_x, playerAction.location_y);
    }

    return;
}

//
void Logic::processMovement(unsigned int pid, unsigned int p_x, unsigned int p_y)
{

    _playersPositions[pid]->x = p_x;
    _playersPositions[pid]->y = p_y;

    std::cout << _playersPositions[pid]->x << " " << _playersPositions[pid]->y << "\n";

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

//void 
void Logic::setSender(void* sender)
{
    _sender = sender;
}