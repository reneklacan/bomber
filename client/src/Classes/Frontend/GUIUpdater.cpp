#include "GUIUpdater.h"

using namespace Bomber;
using namespace Bomber::Frontend;
using namespace Bomber::Common;

//
void GUIUpdater::init( Map* map, SpriteBatchNode* node, 
                       std::map<unsigned int, Human *> &players, 
                       Layer* layer, Statistics* stats)
{
    // Init
    _map = map;
    for(auto player : players)
    {
        _players.push_back(player.second);
    }
    _layer = layer;
    _resetNow = false;
    _finishLevel = false;
    _cache = GUICache::getInstance();
    _mediator = Backend::Mediator::getInstance();
    _collisionDetector = new Collisions();
    _statistics = stats;

    // Optimization
    _O_mapPixelHeight = _map->getHeight()*TILE_HEIGHT;
    _O_tileHeightDiv4 = TILE_HEIGHT/4;

    // Ignore items which will be spawned, backend will take care of them
    _map->getTiledMap()->layerNamed("sprites2spawn")->setVisible(false);
    _map->getTiledMap()->layerNamed("effects2spawn")->setVisible(false);

    // Hide sprites, obstacles, effects, portals
    _map->getTiledMap()->layerNamed("sprites")->setVisible(false);
    _map->getTiledMap()->layerNamed("obstacles")->setVisible(false);
    _map->getTiledMap()->layerNamed("effects")->setVisible(false);
    _map->getTiledMap()->layerNamed("portals")->setVisible(false);

    // Init Batch Node
    _batchNode = node;
    _batchNode->setTag(0);

    // Add BatchNode
    _map->addChild(_batchNode);

    // Initialize player
    this->initPlayers();

    // Cache data from tiled map layers
    _cache->setBatchNode(_batchNode);   // Batch Node init must be first
    _cache->cacheAllLayers(_map);
    _cache->initCaches(_map);

    // Initialize all important layers
    this->initLayers();

    // Init Collision Detector
    _collisionDetector->setMapDimensions(_map->getWidth(), _map->getHeight());
    _collisionDetector->setObstacles(&_obstacles);
    _collisionDetector->setBombs(&_bombs);
}

//
void GUIUpdater::update()
{
    GameState* state = _mediator->getState();
    auto changes = state->getChangesFromId(_lastChangeID);

    _lastChangeID = changes.first;
    for(auto change : changes.second)
    {
        GameStateChange *GSChange = change;

        switch(GSChange->getType())
        {
            // Move
            case SPRITE_MOVE:
            {
                this->updateSpriteMove( (GSCSpriteMove *)GSChange );
            }
            break;
            // Portals
            case SPRITE_TELEPORT:
            {
                this->updateSpriteTeleport( (GSCSpriteTeleport *)GSChange);
            }
            break;
            // Bomb spawn
            case BOMB_SPAWN:
            {
                this->updateBombSpawn( (GSCBombSpawn *)GSChange );
            }
            break;
            // Bomb destroy
            case BOMB_DESTROY:
            {
                this->updateBombDestroy( (GSCBombDestroy *)GSChange );
            }
            break;
            // Obstacle destroy
            case OBSTACLE_DESTROY:
            {
                this->updateObstacleDestroy( (GSCObstacleDestroy *)GSChange );
            }
            break;
            // Explosion
            case EXPLOSION_SPAWN:
            {
                this->updateExplosionSpawn( (GSCExplosionSpawn *)GSChange );
                
            }
            break;
            case ACHIEVEMENT_UNLOCKED:
            {
                this->updateAchievementUnlocked( (GSCAchievementUnlocked *)GSChange );
            }
            break;
            case OBSTACLE_SPAWN:
            {
                this->updateObstacleSpawn( (GSCObstacleSpawn *)GSChange );
            }
            break;
            case SPRITE_DESTROY:
            {
                this->updateSpriteDestroy( (GSCSpriteDestroy *)GSChange );
            }
            break;
            case LEVER_SWITCH_ON:
            {
                this->updateLeverSwitchOn( (GSCLeverSwitchOn *)GSChange );
            }
            break;
            case LEVER_SWITCH_OFF:
            {
                this->updateLeverSwitchOff( (GSCLeverSwitchOff *)GSChange );
            }
            break;
            case SPRITE_DAMAGE:
            {
                this->updateSpriteDamage( (GSCSpriteDamage *)GSChange );
            }
            break;
            case SPRITE_ATTR_UPDATE:
            {
                this->updateSpriteAttrUpdate( (GSCSpriteAttrUpdate *)GSChange );
            }
            break;
            case EFFECT_DESTROY:
            {
                this->updateEffectDestroy( (GSCEffectDestroy *)GSChange );
            }
            break;
            case SPRITE_SPAWN:
            {
                this->updateSpriteSpawn( (GSCSpriteSpawn *)GSChange );
            }
            break;
            case EFFECT_SPAWN:
            {
                this->updateEffectSpawn( (GSCEffectSpawn *)GSChange );
            }
            break;
            case LEVEL_RESET:
            {
                this->updateLevelReset( (GSCLevelReset *)GSChange );
            }
            break;
            case LEVEL_FINISH:
            {
                this->updateLevelFinish( (GSCLevelFinish *)GSChange );
            }
            break;
            case BOMB_MOVE:
            {
                this->updateBombMove( (GSCBombMove *)GSChange );
            }
            break;
            case BLOCK_PUSH:
            {
                this->updateBlockPush( (GSCBlockPush *)GSChange );
            }
            break;
            // Nothing    
            default: {}
        }
    }

    return;
}

//
void GUIUpdater::updateSpriteMove(GSCSpriteMove *spriteMove)
{
    unsigned int spriteID = spriteMove->getGameObjectId();

    for(auto player : _players)
    {
        if (spriteID == player->getID())
        {
            // Only set Z coordinate
            _batchNode->reorderChild(
                player, 
                _O_mapPixelHeight - player->getPosition().y
            );
            return;
        }
    }

    // Sprite is already initialized
    if (_mobs.find(spriteID) != _mobs.end())
    {
        Point newPosition = ccp (
            spriteMove->getPosition().x,
            spriteMove->getPosition().y
        );
        _mobs[spriteID]->updatePosition( newPosition );
        _batchNode->reorderChild(
            _mobs[spriteID],
            _O_mapPixelHeight - spriteMove->getPosition().y - _O_tileHeightDiv4 // DO NOT CHANGE
        );
    }
    // First occurence of a sprite
    else
    {
        std::cerr << "Unitialized sprite: " << spriteMove->getGameObjectId() << std::endl;
    }

    return;
}


//
void GUIUpdater::updateSpriteTeleport(GSCSpriteTeleport *spriteTeleport)
{
    // Player, map needs to be moved
    for(auto player : _players)
    {
        if(spriteTeleport->getGameObjectId() == player->getID())
        {
            Point playerPosition = player->getPosition();
            Point teleportPosition = ccp( spriteTeleport->getPosition().x, spriteTeleport->getPosition().y);
            player->updatePosition(teleportPosition);
            if(player->getID() == 19991)    // TODO: ID Management
            {
                _map->addToPosition(ccpSub(playerPosition, teleportPosition));
            }
            return;
        }
    }

    // Else Mob
    _mobs[spriteTeleport->getGameObjectId()]->updatePosition(
        ccp (
            spriteTeleport->getPosition().x,
            spriteTeleport->getPosition().y
        )
    );

    return; // CHILD REORDER ?
}

//
void GUIUpdater::updateBombSpawn(GSCBombSpawn *bombSpawn)
{

    unsigned int id = bombSpawn->getGameObjectId();
    Point bombSpawnPosition = ccp( bombSpawn->getPosition().x, bombSpawn->getPosition().y);

    _bombs[ id ] = _cache->getBomb(
        _batchNode->getTexture(),
        Shapes::pickImageFromTexture(BOMB_IMAGE_ID)
    );

    _bombs[ id ]->setPosition(bombSpawnPosition);
    _batchNode->reorderChild(_bombs[ id ], _O_mapPixelHeight - bombSpawnPosition.y);

    // for kicking
    CollisionArea* ca = new CollisionArea();
    ca->setPoint(bombSpawnPosition);
    std::vector<unsigned int> pIDs;
    for(auto player : _players)
    {
        pIDs.push_back( player->getID() );
    }
    ca->setPlayersID(pIDs);
    _collisionDetector->setCFA(id, ca);

    return;
}

//
void GUIUpdater::updateBombDestroy(GSCBombDestroy *bombDestroy)
{
    unsigned int id = bombDestroy->getGameObjectId();
    // Cache or remove         
    if ( !_cache->cacheBomb(_bombs[ id ]) )
    {
        _batchNode->removeChild(_bombs[ id ], true);
    }
    _bombs.erase(id);
}

//
void GUIUpdater::updateObstacleDestroy(GSCObstacleDestroy *obstacleDestroy)
{
    int bombID = (_map->getHeight() - ( obstacleDestroy->getGameObjectId() / _map->getWidth() ) - 1) 
                * _map->getWidth()
                + obstacleDestroy->getGameObjectId() % _map->getWidth();
    // Cache or remove         
    if ( !_cache->cacheObstacle(_obstacles[bombID]) )
    {
        _batchNode->removeChild(_obstacles[bombID], true);
    }
    _obstacles.erase(bombID); // Collision detection

}

//
void GUIUpdater::updateExplosionSpawn(GSCExplosionSpawn *explosionSpawn)
{
    Point epicentrum = ccp(explosionSpawn->getEpicentrum().x, explosionSpawn->getEpicentrum().y);
    Explosion *explosion = new Explosion(
        epicentrum,
        explosionSpawn->getLeftArmLength(),
        explosionSpawn->getRightArmLength(),
        explosionSpawn->getTopArmLength(),
        explosionSpawn->getBottomArmLength()
    );
    explosion->autorelease();
    _map->addChild(explosion, 0);
    return;
}

//
void GUIUpdater::updateAchievementUnlocked(GSCAchievementUnlocked *achievementUnlocked)
{

    AchievementButton *ab = new AchievementButton(
        achievementUnlocked->getTitle(),
        achievementUnlocked->getDescription(),
        ""
    );
    ButtonLayer::getInstance()->addToAchievements(ab);

    // stats
    _statistics->noteAchievementUnlock();

    return;
}

//
void GUIUpdater::updateObstacleSpawn(GSCObstacleSpawn *obstacleSpawn)
{
    unsigned int ix = obstacleSpawn->getCoordinates().x;
    unsigned int iy = obstacleSpawn->getCoordinates().y;
    unsigned int transformed_iy = _map->getHeight() - iy - 1;
    int position = _map->getWidth() * transformed_iy + ix;

    // Init with texture of Batch Node
    _obstacles[ position ] = _cache->getObstacle(
        _batchNode->getTexture(),
        Shapes::pickImageFromTexture( obstacleSpawn->getGid() )
    );

    // Add to Batch Node
    _obstacles[ position ]->setPosition( ccp(ix*TILE_WIDTH, iy*TILE_HEIGHT ) );
    _batchNode->reorderChild(_obstacles[ position ], transformed_iy*TILE_HEIGHT+5);

    return;
}

//
void GUIUpdater::updateSpriteDestroy( GSCSpriteDestroy *spriteDestroy )
{
    int playerToDestroy = -1;
    int counter = 0;
    for(auto player : _players)
    {
        if(spriteDestroy->getGameObjectId() == player->getID())
        {
            _batchNode->removeChild(player, true); // WARNING
            player->setIsAlive(false);
            playerToDestroy = counter;
        }
        counter++;
    }
    if(playerToDestroy != -1)
    {
        _players.erase(_players.begin() + playerToDestroy);
        if(_players.size() == 0)
        {
            _collisionDetector->skipEval(true);
        }
        return;
    }

    unsigned int id = spriteDestroy->getGameObjectId();
    // Cache or remove         
    if ( !_cache->cacheSprite(_mobs[id]) )
    {
        _batchNode->removeChild(_mobs[id], true);

        //TEST
        Bubble *bb = new Bubble("The Evil Bitcher", "How dare you, you little shit ?", "");
        ButtonLayer::getInstance()->addToBubbles(bb);
    }
    _mobs.erase(id);
}

//
void GUIUpdater::updateLeverSwitchOn( GSCLeverSwitchOn *leverSwitchOn )
{
    return; // TODO
}

//
void GUIUpdater::updateLeverSwitchOff( GSCLeverSwitchOff *leverSwitchOff )
{
    return; // TODO
}

//
void GUIUpdater::updateSpriteDamage( GSCSpriteDamage *spriteDamage )
{
    return; // TODO
}

//
void GUIUpdater::updateSpriteAttrUpdate( GSCSpriteAttrUpdate *spriteAttrUpdate )
{
    // Show only players buff
    Human *sprite = NULL;

    for(auto player : _players)
    {
        if (spriteAttrUpdate->getGameObjectId() == player->getID())
        {
            sprite = player;
            break;
        }
    }

    if (sprite == NULL)
    {
        return;
    }

    // Get buff image
    unsigned int imageID = spriteAttrUpdate->getGid();
    switch(spriteAttrUpdate->getEffectType())
    {
        case Backend::EFFECT_BOMB_CAPACITY_INC:
        case Backend::EFFECT_BOMB_POWER_INC:
        case Backend::EFFECT_FIRE_IMMUNITY:
        case Backend::EFFECT_WATER_IMMUNITY:
        case Backend::EFFECT_CLEAR_IMMUNITIES:
            break;
        case Backend::EFFECT_SPEED_INC:
            sprite->setSpeed(sprite->getSpeed() + SPRITE_SPEED_INCREASE);
            break;
        case Backend::EFFECT_FIRE_TRAP:
        case Backend::EFFECT_WATER_TRAP:
            return;
        default:
            std::cerr << "Unknown effect type: " << 
                spriteAttrUpdate->getEffectType() << std::endl;
            return; // Unknown effect type
    }

    // Create or update buff button
    if (spriteAttrUpdate->getEffectType() == Backend::EFFECT_CLEAR_IMMUNITIES)
    {
        // TODO: find out fix to this ugly workaround
        ButtonLayer::getInstance()->removeBuff(638);
        ButtonLayer::getInstance()->removeBuff(639);
    }
    else if (ButtonLayer::getInstance()->isInBuffs(imageID))
    {
        ButtonLayer::getInstance()->incrementBuff(imageID);
    }
    else
    {
        EffectButton *eb = new EffectButton(
            imageID,
            Shapes::pickImageFromTexture( imageID ),
            _batchNode->getTexture()
        );
        ButtonLayer::getInstance()->addToBuffs(eb);
    }

    return;
}

//
void GUIUpdater::updateEffectDestroy( GSCEffectDestroy *effectDestroy )
{
    int id = (_map->getHeight() - ( effectDestroy->getGameObjectId() / _map->getWidth() ) - 1) 
                * _map->getWidth()
                + effectDestroy->getGameObjectId() % _map->getWidth();
    // Cache or remove         
    if ( !_cache->cacheEffect(_effects[id]) )
    {
        _batchNode->removeChild(_effects[id], true);
    }
    _effects.erase(id);
    return;
}

//
void GUIUpdater::updateSpriteSpawn( GSCSpriteSpawn *spriteSpawn )
{
    unsigned int ix = spriteSpawn->getCoordinates().x;
    unsigned int iy = spriteSpawn->getCoordinates().y;
    unsigned int transformed_iy = _map->getHeight() - iy - 1;
    unsigned int id = spriteSpawn->getGameObjectId();
    Rect imageRect = Shapes::pickImageFromTexture( spriteSpawn->getGid() );
    // Init with texture of Batch Node
    _mobs[ id ] = _cache->getSprite(
        _batchNode->getTexture(),
        imageRect
    );

    // Position and Batch node Z order
    _mobs[ id ]->spawnPosition( ccp(ix*TILE_WIDTH, iy*TILE_HEIGHT ) );
    _mobs[ id ]->updateDefaultImage(imageRect);
    _batchNode->reorderChild(_mobs[ id ], transformed_iy*TILE_HEIGHT);

    return;
}

//
void GUIUpdater::updateEffectSpawn( GSCEffectSpawn *effectSpawn )
{
    unsigned int ix = effectSpawn->getCoordinates().x;
    unsigned int iy = effectSpawn->getCoordinates().y;
    unsigned int transformed_iy = _map->getHeight() - iy - 1;
    int position = _map->getWidth() * transformed_iy + ix;

    // Init with texture of Batch Node
    _effects[ position ] = _cache->getEffect(
        _batchNode->getTexture(),
        Shapes::pickImageFromTexture( effectSpawn->getGid() ) 
    );

    // Position and Batch node Z order
    _effects[ position ]->setPosition( ccp(ix*TILE_WIDTH, iy*TILE_HEIGHT ) );
    _batchNode->reorderChild(_effects[ position ], transformed_iy*TILE_HEIGHT+5);

    return;
}

//
void GUIUpdater::updateLevelReset( GSCLevelReset *levelReset )
{
    _resetNow = true;
    return;
}

//
void GUIUpdater::updateLevelFinish( GSCLevelFinish *levelFinish )
{
    // Buffs and Achievements
    ButtonLayer::getInstance()->resetAll();
    // Cache
    _cache->resetSprites();
    // Collisions
    _collisionDetector->reset();
    // Players
    _players.clear();
    // Instance variable
    _resetNow = false;
    _finishLevel = false; // hmm ?
    // Statistics
    _statistics->setBombSpawns(levelFinish->getBombSpawns());
    _statistics->setKilledMonsters(levelFinish->getTotalKills());
    _statistics->setTakenBuffs(levelFinish->getTotalEffects());
    _statistics->setDestroyedObstacles(levelFinish->getTotalObstacles());
    _statistics->setTeleportations(levelFinish->getTeleportUses());
    _statistics->setUsedLevers(levelFinish->getLeverUses());
    // Flag
    _finishLevel = true;
    return;
}

//
void GUIUpdater::updateBombMove( GSCBombMove *bombMove )
{
    unsigned int id = bombMove->getGameObjectId();
    _bombs[ id ]->setPosition( ccp( bombMove->getPosition().x, bombMove->getPosition().y) );
    _batchNode->reorderChild(_bombs[ id ], _O_mapPixelHeight - bombMove->getPosition().y);
    return;
}

//
void GUIUpdater::updateBlockPush( GSCBlockPush *blockPush )
{
    // Get obstacle for animation
    unsigned int id = _map->getWidth() * (_map->getHeight() - blockPush->getFrom().y - 1) + blockPush->getFrom().x;
    unsigned int newId = _map->getWidth() * (_map->getHeight() - blockPush->getTo().y - 1) + blockPush->getTo().x;
    Sprite *obstacle = _obstacles[ id ];

    // If no such obstacle exists, return
    if(obstacle == NULL)
    {
        return;
    }

    // Important actions for collision detection and callback
    _collisionDetector->setObstacleImmuneToPush(id);

    // Create Obstacle Move data object
    ObstacleMove* obsMove = new ObstacleMove(id, newId, obstacle);
    
    // Create callback function a bind it with data object 
    std::function<void()> cleaner = std::bind(&GUIUpdater::finishUpdateBlockPush, this, obsMove);

    // Create animation
    obstacle->runAction(
        Sequence::create( 
            MoveTo::create(
                0.5,
                ccp(
                    blockPush->getTo().x * TILE_WIDTH,
                    blockPush->getTo().y * TILE_HEIGHT
                )
            ),
            CallFunc::create(
                cleaner
            ),
            NULL
        )
    );

    return;
}

//
void GUIUpdater::finishUpdateBlockPush(ObstacleMove *move)
{
    // Update collisions
    _collisionDetector->unsetObstacleImmuneToPush( move->getFrom() );

    // Erase old block from map
    _obstacles.erase( move->getFrom() );

    // Save moved obstacle with new id
    _obstacles[ move->getTo() ] = move->getSprite();
    _batchNode->reorderChild(
        _obstacles[ move->getTo() ], 
        _O_mapPixelHeight - move->getSprite()->getPosition().y - TILE_HEIGHT + 5
    );

    delete move;
}

/*
 * ========== 
 *  General
 * ==========
 */

bool GUIUpdater::obstacleExists(unsigned int id)
{
    if( _obstacles[ id ] != NULL )
    {
        return true;
    }
    return false;
}

bool GUIUpdater::isPlayerAlive(unsigned int id)
{
    for(auto player : _players)
    {
        if(player->getID() == id)
        {
            return true;
        }
    }
    return false;
}

/*
 * ========== 
 * Collisions
 * ==========
 */
 
//
std::vector<bool> GUIUpdater::evalCollisions(Human *sprite)
{
    // Eval collisions
    return _collisionDetector->eval(sprite);
}

/*
 * ========== 
 *    Init
 * ==========
 */

//
void GUIUpdater::initPlayers()
{
    for(auto player : _players)
    {
        // All initialization
        player->updateDefaultImage( Shapes::pickImageFromTexture(HUMAN_IMAGE_ID) );
        player->resetRotations();
        player->setSpeed(200);
        player->retain();
        player->setAnchorPoint(ccp(0.45f, 0.2f));
        player->setVertexZ(0);

        // Add player to Batch Node
        _batchNode->addChild(player, 0);
        _batchNode->reorderChild(
            player, 
            _O_mapPixelHeight - player->getPosition().y
        );
    }
}

//
void GUIUpdater::initLayers()
{
    // Clear
    _mobs.clear();
    _obstacles.clear();
    _effects.clear();
    _bombs.clear();

    // Init obstacles, mobs and effects structure
    for(auto it : *(_cache->getObstacles()) )
    {
        unsigned int id = it.first;
        Sprite *sp = it.second;

        _obstacles[ id ] = Sprite::createWithTexture( sp->getTexture(), sp->getTextureRect() );
        _obstacles[ id ]->setPosition( sp->getPosition() );
        _obstacles[ id ]->setAnchorPoint( ccp(0, 0) );
        _obstacles[ id ]->setVertexZ(0); // DO NOT CHANGE

        _batchNode->addChild(_obstacles[ id ], 0);
        _batchNode->reorderChild(
            _obstacles[ id ],
            _O_mapPixelHeight - sp->getPosition().y + 5
        );
    }
    for(auto it : *(_cache->getMobs()) )
    {
        unsigned int id = it.first;
        Sprite *sp = it.second;

        //_mobs[ id ] = Sprite::createWithTexture( sp->getTexture(), sp->getTextureRect() );
        _mobs[ id ] = new ActionSprite( sp->getTexture(), sp->getTextureRect() );
        _mobs[ id ]->spawnPosition( sp->getPosition() );
        _mobs[ id ]->setAnchorPoint( ccp(0, 0) );
        _mobs[ id ]->setVertexZ(0); // DO NOT CHANGE

        _batchNode->addChild(_mobs[ id ], 0);
        _batchNode->reorderChild(
            _mobs[ id ],
            _O_mapPixelHeight - sp->getPosition().y - TILE_HEIGHT/4
        );
    }
    for(auto it : *(_cache->getEffects()) )
    {
        unsigned int id = it.first;
        Sprite *sp = it.second;

        _effects[ id ] = Sprite::createWithTexture( sp->getTexture(), sp->getTextureRect() );
        _effects[ id ]->setPosition( sp->getPosition() );
        _effects[ id ]->setAnchorPoint( ccp(0, 0) );
        _effects[ id ]->setVertexZ(0); // DO NOT CHANGE

        _batchNode->addChild(_effects[ id ], 0);
        _batchNode->reorderChild(
            _effects[ id ],
            _O_mapPixelHeight - sp->getPosition().y + 5
        );
    }
    for(auto it : *(_cache->getPortals()) )
    {
        unsigned int id = it.first;
        Sprite *sp = it.second;

        _portals[ id ] = Sprite::createWithTexture( sp->getTexture(), sp->getTextureRect() );
        _portals[ id ]->setPosition( sp->getPosition() );
        _portals[ id ]->setAnchorPoint( ccp(0, 0) );
        _portals[ id ]->setVertexZ(0); // DO NOT CHANGE

        _batchNode->addChild(_portals[ id ], 0);
        _batchNode->reorderChild(
            _portals[ id ],
            _O_mapPixelHeight - sp->getPosition().y + 5
        );
    }

    return;
}

/*
 * ========== 
 *   Reset
 * ==========
 */

//
void GUIUpdater::resetGUI(std::map<unsigned int, Human *> &players)
{
    // Buffs and Achievements
    ButtonLayer::getInstance()->reset();

    // Batch Node
    _batchNode->removeAllChildrenWithCleanup(true);
    this->initLayers();

    // Cache
    _cache->resetSprites();
    _cache->initCaches(_map);

    // Players
    _players.clear();
    for(auto player : players)
    {
        player.second->setIsAlive(true);   // Otherwise he could not plant a bomb
        _players.push_back(player.second);
    }
    this->initPlayers();

    // Collisions
    _collisionDetector->reset();

    // Init instance variable
    _resetNow = false;
    _finishLevel = false;

    return;
}
