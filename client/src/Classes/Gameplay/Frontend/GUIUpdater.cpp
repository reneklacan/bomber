#include "GUIUpdater.h"

using namespace Bomber;
using namespace Bomber::Frontend;

//
GUIUpdater *GUIUpdater::getInstance()
{
    static GUIUpdater instance;
    return &instance;
}

//
void GUIUpdater::init( Map* map, Human* player, Layer* layer)
{
    _map = map;
    _player = player;
    _layer = layer;
    _mobs.clear();
    _obstacles.clear();
    _effects.clear();

    // Init Batch Node
    _batchNode = SpriteBatchNode::create("tiles/tileset.png");
    _batchNode->setTag(0);

    // Add BatchNode
    _map->addChild(_batchNode);

    // Add player to Batch Node
    _player->initWithTexture(_batchNode->getTexture(), CCRectMake(120,60,80,110));
    _player->retain();
    _player->setAnchorPoint(ccp(0.45f, 0.2f));
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Point origin = Director::sharedDirector()->getVisibleOrigin();
    _player->setPosition(
            ccp(
                origin.x + _player->getContentSize().width/2 + 101 + 50,
                origin.y + visibleSize.height/2
            )
    );
    _player->setNextPosition(_player->getPosition());
    _player->setVertexZ(0);
    _batchNode->addChild(_player, 0);

    // Hide sprites
    TMXLayer *spritesLayer = _map->getTiledMap()->layerNamed("sprites");
    spritesLayer->setVisible(false);

    // Hide obstacles
    _obstaclesLayer = _map->getTiledMap()->layerNamed("obstacles");
    _obstaclesLayer->setVisible(false);

    // Hide effects
    TMXLayer *effectsLayer = _map->getTiledMap()->layerNamed("effects");
    effectsLayer->setVisible(false);

    // Init obstacles, mobs and effects structure
    for(int ix = 0; ix < _map->getWidth(); ix++)
    {
        for(int iy = 0; iy < _map->getHeight(); iy++)
        {
            Point point = ccp(ix, iy);
            if(_obstaclesLayer->tileGIDAt( point ) != 0)
            {
                int position = _map->getWidth() * iy + ix;
                _obstacles[ position ] = _obstaclesLayer->tileAt( point );
                _batchNode->addChild(_obstacles[ position ], 0);
                _batchNode->reorderChild(_obstacles[ position ], iy*TILE_HEIGHT+5);
                _obstacles[ position ]->setVertexZ(0); // DO NOT CHANGE
            }

            if(spritesLayer->tileGIDAt( point ) != 0)
            {
                int position = _map->getWidth() * (_map->getHeight() - iy - 1) + ix;
                _mobs[ position ] = spritesLayer->tileAt( point );
                _batchNode->addChild(_mobs[ position ], 0);
                _mobs[ position ]->setPosition( point );
                _batchNode->reorderChild(_mobs[ position ], iy*TILE_HEIGHT);
                _mobs[ position ]->setVertexZ(0); // DO NOT CHANGE
            }

            if(effectsLayer->tileGIDAt( point ) != 0)
            {
                int position = _map->getWidth() * iy + ix;
                _effects[ position ] = effectsLayer->tileAt( point );
                _batchNode->addChild(_effects[ position ], 0);
                _batchNode->reorderChild(_effects[ position ], iy*TILE_HEIGHT);
                _effects[ position ]->setVertexZ(0); // DO NOT CHANGE
            }

        }
    }

    // Set map view
    _map->setPosition(
            ccp(
                visibleSize.width/2 - _player->getPosition().x,
                0
            )
    );

}

//
void GUIUpdater::update(Point playerPosition)
{
    Backend::GameState* state = Backend::Mediator::getInstance()->getState();
    auto changes = state->getChangesFromId(_lastChangeID);

    _lastChangeID = changes.first;
    for(auto change : changes.second)
    {
        Backend::GameStateChange *GSChange = change;

        switch(GSChange->getType())
        {
            // Move
            case Backend::SPRITE_MOVE:
            {
                this->updateSpriteMove( (Backend::GSCSpriteMove *)GSChange );
            }
            break;
            // Portals
            case Backend::SPRITE_TELEPORT:
            {
                this->updateSpriteTeleport( (Backend::GSCSpriteTeleport *)GSChange, playerPosition );
            }
            break;
            // Bomb spawn
            case Backend::BOMB_SPAWN:
            {
                this->updateBombSpawn( (Backend::GSCBombSpawn *)GSChange );
            }
            break;
            // Bomb destroy
            case Backend::BOMB_DESTROY:
            {
                this->updateBombDestroy( (Backend::GSCBombDestroy *)GSChange );
            }
            break;
            // Obstacle destroy
            case Backend::OBSTACLE_DESTROY:
            {
                this->updateObstacleDestroy( (Backend::GSCObstacleDestroy *)GSChange );
                
            }
            break;
            // Explosion
            case Backend::EXPLOSION_SPAWN:
            {
                this->updateExplosionSpawn( (Backend::GSCExplosionSpawn *)GSChange );
                
            }
            break;
            case Backend::ACHIEVEMENT_UNLOCKED:
            {
                this->updateAchievementUnlocked( (Backend::GSCAchievementUnlocked *)GSChange );
            }
            break;
            case Backend::OBSTACLE_SPAWN:
            {
                this->updateObstacleSpawn( (Backend::GSCObstacleSpawn *)GSChange );
            }
            break;
            case Backend::SPRITE_DESTROY:
            {
                this->updateSpriteDestroy( (Backend::GSCSpriteDestroy *)GSChange );
            }
            break;
            case Backend::LEVER_SWITCH_ON:
            {
                this->updateLeverSwitchOn( (Backend::GSCLeverSwitchOn *)GSChange );
            }
            break;
            case Backend::LEVER_SWITCH_OFF:
            {
                this->updateLeverSwitchOff( (Backend::GSCLeverSwitchOff *)GSChange );
            }
            break;
            case Backend::SPRITE_DAMAGE:
            {
                this->updateSpriteDamage( (Backend::GSCSpriteDamage *)GSChange );
            }
            break;
            case Backend::SPRITE_ATTR_UPDATE:
            {
                this->updateSpriteAttrUpdate( (Backend::GSCSpriteAttrUpdate *)GSChange );
            }
            break;
            case Backend::EFFECT_DESTROY:
            {
                this->updateEffectDestroy( (Backend::GSCEffectDestroy *)GSChange );
            }
            break;
            case Backend::SPRITE_SPAWN:
            {
                this->updateSpriteSpawn( (Backend::GSCSpriteSpawn *)GSChange );
            }
            break;
            case Backend::EFFECT_SPAWN:
            {
                this->updateEffectSpawn( (Backend::GSCEffectSpawn *)GSChange );
            }
            break;
            // Nothing    
            default: {}
        }
    }

    return;
}

//
void GUIUpdater::updateSpriteMove(Backend::GSCSpriteMove *spriteMove)
{
    if(spriteMove->getGameObjectId() == _player->getID())
    {
        // Only set Z coordinate
        _batchNode->reorderChild(
            _player, 
            _map->getHeight()*TILE_HEIGHT - _player->getPosition().y
        );
        return;
    }

    // Sprite is already initialized
    if( _mobs.find(spriteMove->getGameObjectId()) != _mobs.end() )
    {
        _mobs[spriteMove->getGameObjectId()]->setPosition(
                    ccp (
                        spriteMove->getPosition().x,
                        spriteMove->getPosition().y
                    )
                );
        _batchNode->reorderChild(
            _mobs[spriteMove->getGameObjectId()],
            _map->getHeight()*TILE_HEIGHT - spriteMove->getPosition().y - TILE_HEIGHT/4 // DO NOT CHANGE
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
void GUIUpdater::updateSpriteTeleport(Backend::GSCSpriteTeleport *spriteTeleport, Point playerPosition)
{
    // Player, map needs to be moved
    if(spriteTeleport->getGameObjectId() == _player->getID())
    {
        Point teleportPosition = ccp( spriteTeleport->getPosition().x, spriteTeleport->getPosition().y);
        _player->setPosition(teleportPosition);
        _map->addToPosition(ccpSub(playerPosition, teleportPosition));
    }
    // Mob
    else
    {
        _mobs[spriteTeleport->getGameObjectId()]->setPosition(
                    ccp (
                        spriteTeleport->getPosition().x,
                        spriteTeleport->getPosition().y
                    )
                );
    }
    return;
}

//
void GUIUpdater::updateBombSpawn(Backend::GSCBombSpawn *bombSpawn)
{
    Point bombSpawnPosition = ccp( bombSpawn->getPosition().x, bombSpawn->getPosition().y);
    Point tilemapPosition = _player->getTilemapPosition(); // WARNING
    Bomb *bomb = Bomb::create(_map, _batchNode, _player);
    _batchNode->reorderChild(bomb, _map->getHeight()*TILE_HEIGHT - tilemapPosition.y*TILE_HEIGHT - TILE_HEIGHT);
    bomb->setPosition(bombSpawnPosition);
    bomb->setTilemapPosition( ccp(tilemapPosition.x, tilemapPosition.y) );
    _map->addBomb(bombSpawn->getGameObjectId(), bomb);
    return;
}

//
void GUIUpdater::updateBombDestroy(Backend::GSCBombDestroy *bombDestroy)
{
    Bomb *bomb = (Bomb *)_map->getBomb( bombDestroy->getGameObjectId() );
    bomb->setVisible(false);
    bomb->setDetonated();
    _map->removeBomb(bombDestroy->getGameObjectId());
    _batchNode->removeChild(bomb, true); // WARNING
}

//
void GUIUpdater::updateObstacleDestroy(Backend::GSCObstacleDestroy *obstacleDestroy)
{
    int bombID = (_map->getHeight() - ( obstacleDestroy->getGameObjectId() / _map->getWidth() ) - 1) 
                * _map->getWidth()
                + obstacleDestroy->getGameObjectId() % _map->getWidth();
    _obstacles[bombID]->setVisible(false);
    _batchNode->removeChild(_obstacles[bombID], true); // WARNING
    _obstacles.erase(bombID); // Collision detection

}

//
void GUIUpdater::updateExplosionSpawn(Backend::GSCExplosionSpawn *explosionSpawn)
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
void GUIUpdater::updateAchievementUnlocked(Backend::GSCAchievementUnlocked *achievementUnlocked)
{

    AchievementButton *ab = new AchievementButton(
        achievementUnlocked->getTitle(),
        achievementUnlocked->getDescription(),
        ""
    );
    ButtonLayer::getInstance()->addToAchievements(ab);
    return;
}

//
void GUIUpdater::updateObstacleSpawn(Backend::GSCObstacleSpawn *obstacleSpawn)
{
    unsigned int ix = obstacleSpawn->getCoordinates().x;
    unsigned int iy = obstacleSpawn->getCoordinates().y;
    unsigned int transformed_iy = _map->getHeight() - iy - 1;
    int position = _map->getWidth() * transformed_iy + ix;

    // Init with texture of Batch Node
    _obstacles[ position ] = Sprite::createWithTexture(
        _batchNode->getTexture(),
        this->pickImageFromTexture( obstacleSpawn->getGid() ) 
    );    // Maybe cache ?

    // Add to Batch Node
    _obstacles[ position ]->setPosition( ccp(ix*TILE_WIDTH, iy*TILE_HEIGHT ) );
    _obstacles[ position ]->setAnchorPoint( ccp(0, 0) );
    _batchNode->addChild(_obstacles[ position ], 0);
    _batchNode->reorderChild(_obstacles[ position ], transformed_iy*TILE_HEIGHT+5);
    _obstacles[ position ]->setVertexZ(0); // DO NOT CHANGE
    return;
}

//
void GUIUpdater::updateSpriteDestroy( Backend::GSCSpriteDestroy *spriteDestroy )
{
    unsigned int id = spriteDestroy->getGameObjectId();
    _mobs[ id ]->setVisible(false);
    _batchNode->removeChild(_mobs[id], true); // WARNING
    _mobs.erase(id);
}

//
void GUIUpdater::updateLeverSwitchOn( Backend::GSCLeverSwitchOn *leverSwitchOn )
{
    return; // TODO
}

//
void GUIUpdater::updateLeverSwitchOff( Backend::GSCLeverSwitchOff *leverSwitchOff )
{
    return; // TODO
}

//
void GUIUpdater::updateSpriteDamage( Backend::GSCSpriteDamage *spriteDamage )
{
    return; // TODO
}

//
void GUIUpdater::updateSpriteAttrUpdate( Backend::GSCSpriteAttrUpdate *spriteAttrUpdate )
{
    //std::cout << spriteAttrUpdate->getGameObjectId() << "\n";
    //std::cout << spriteAttrUpdate->getEffectType() << "\n";
    return;
}

//
void GUIUpdater::updateEffectDestroy( Backend::GSCEffectDestroy *effectDestroy )
{
    int id = (_map->getHeight() - ( effectDestroy->getGameObjectId() / _map->getWidth() ) - 1) 
                * _map->getWidth()
                + effectDestroy->getGameObjectId() % _map->getWidth();
    _effects[id]->setVisible(false);
    _batchNode->removeChild(_effects[id], true); // WARNING
    _effects.erase(id);
    return;
}

//
void GUIUpdater::updateSpriteSpawn( Backend::GSCSpriteSpawn *spriteSpawn )
{
    unsigned int ix = spriteSpawn->getCoordinates().x;
    unsigned int iy = spriteSpawn->getCoordinates().y;
    unsigned int transformed_iy = _map->getHeight() - iy - 1;
    unsigned int id = spriteSpawn->getGameObjectId();

    // Init with texture of Batch Node
    _mobs[ id ] = Sprite::createWithTexture(
        _batchNode->getTexture(),
        this->pickImageFromTexture(spriteSpawn->getGid()) 
    );    // Maybe cache ?

    // Add to Batch Node
    _mobs[ id ]->setPosition( ccp(ix*TILE_WIDTH, iy*TILE_HEIGHT ) );
    _mobs[ id ]->setAnchorPoint( ccp(0, 0) );
    _batchNode->addChild(_mobs[ id ], 0);
    _batchNode->reorderChild(_mobs[ id ], transformed_iy*TILE_HEIGHT);
    _mobs[ id ]->setVertexZ(0); // DO NOT CHANGE
    return;
}

//
void GUIUpdater::updateEffectSpawn( Backend::GSCEffectSpawn *effectSpawn )
{
    unsigned int ix = effectSpawn->getCoordinates().x;
    unsigned int iy = effectSpawn->getCoordinates().y;
    unsigned int transformed_iy = _map->getHeight() - iy - 1;
    int position = _map->getWidth() * transformed_iy + ix;

    // Init with texture of Batch Node
    _effects[ position ] = Sprite::createWithTexture(
        _batchNode->getTexture(),
        this->pickImageFromTexture( effectSpawn->getGid() ) 
    );    // Maybe cache ?

    // Add to Batch Node
    _effects[ position ]->setPosition( ccp(ix*TILE_WIDTH, iy*TILE_HEIGHT ) );
    _effects[ position ]->setAnchorPoint( ccp(0, 0) );
    _batchNode->addChild(_effects[ position ], 0);
    _batchNode->reorderChild(_effects[ position ], transformed_iy*TILE_HEIGHT+5);
    _effects[ position ]->setVertexZ(0); // DO NOT CHANGE
    return;
}

/*
 * ========== 
 *  General
 * ==========
 */

Rect GUIUpdater::pickImageFromTexture(unsigned int id)
{
    int offset = id % TEXTURE_IMAGES_PER_LINE;
    if( offset == 0 )
    {
        offset = 9;
    }
    offset--;

    return CCRectMake(
        TEXTURE_TILE_WIDTH * offset,
        TEXTURE_TILE_HEIGHT * ( id / (TEXTURE_IMAGES_PER_LINE+1) ),
        TILE_WIDTH,
        TILE_HEIGHT*2
    );
}


/*
 * ========== 
 * Collisions
 * ==========
 */
 
//
std::vector<bool> GUIUpdater::evalCollisions(Point currentPoint, Point nextPoint)
{
    // Init
    std::vector<bool> result;
    result.push_back(false);  // Collision occured
    result.push_back(false);  // Collision on X
    result.push_back(false);  // Collision on Y

    // Partial moves
    Point nextPointX = ccp(nextPoint.x, currentPoint.y);
    Point nextPointY = ccp(currentPoint.x, nextPoint.y);

    // Evaluation
    result[1] = this->evalCollision(nextPointX);
    result[2] = this->evalCollision(nextPointY);
    result[0] = result[1] || result[2];

    // Return
    return result;

}

//
bool GUIUpdater::evalCollision(Point nextPoint)
{
    // Init
    bool result = false;

    // Constants
    int widthLeft = 30;
    int widthRight = 30;
    int heightTop = 20;
    int heightBottom = 0;
    int offsetX = 0;
    int offsetY = 0;

    // Top Left
    offsetX = (nextPoint.x - widthLeft) / TILE_WIDTH;
    offsetY = (nextPoint.y + heightTop) / TILE_HEIGHT;
    if(_obstacles.find(_map->getWidth() * (_map->getHeight() - offsetY -1) + offsetX) != _obstacles.end())
    {
        result = true;
    }
    // Top Right
    offsetX = (nextPoint.x + widthRight) / TILE_WIDTH;
    if(_obstacles.find(_map->getWidth() * (_map->getHeight() - offsetY -1) + offsetX) != _obstacles.end())
    {
        result = true;
    }

    // Bottom Left
    offsetX = (nextPoint.x - widthLeft) / TILE_WIDTH;
    offsetY = (nextPoint.y - heightBottom) / TILE_HEIGHT;
    if(_obstacles.find(_map->getWidth() * (_map->getHeight() - offsetY -1) + offsetX) != _obstacles.end())
    {
        result = true;
    }

    // Bottom Right
    offsetX = (nextPoint.x + widthRight) / TILE_WIDTH;
    if(_obstacles.find(_map->getWidth() * (_map->getHeight() - offsetY -1) + offsetX) != _obstacles.end())
    {
        result = true;
    }

    return result;

}
