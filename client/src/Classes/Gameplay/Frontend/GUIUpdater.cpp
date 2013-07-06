#include "GUIUpdater.h"

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

    _batchNode = SpriteBatchNode::create("tiles/tileset.png");
    _batchNode->setTag(0);

    // Add BatchNode
    _map->addChild(_batchNode);

    // Add player to Batch Node
    //_batchNode->addChild(_player, 0);
    // TMP
    _map->addChild(_player, 0);

    // Hide sprites
    TMXLayer *spritesLayer = _map->getTiledMap()->layerNamed("sprites");
    spritesLayer->setVisible(false);

    // Hide obstacles
    TMXLayer *obstaclesLayer = _map->getTiledMap()->layerNamed("obstacles");
    obstaclesLayer->setVisible(false);

    // Init obstacles structure
    for(int ix = 0; ix < _map->getWidth(); ix++)
    {
        for(int iy = 0; iy < _map->getHeight(); iy++)
        {
            if(obstaclesLayer->tileAt( ccp(ix, iy) ) != 0)
            {
                _obstacles[_map->getWidth() * iy + ix] = obstaclesLayer->tileAt( ccp(ix, iy) );
                _batchNode->addChild(_obstacles[_map->getWidth() * iy + ix], 0);
                //_obstacles[_map->getWidth() * iy + ix]->setZOrder(iy*TILE_HEIGHT+5); // DO NOT CHANGE
                _batchNode->reorderChild(_obstacles[_map->getWidth() * iy + ix], iy*TILE_HEIGHT+5);
                _obstacles[_map->getWidth() * iy + ix]->setVertexZ(0); // DO NOT CHANGE
            }
        }
    }

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
        _player->setZOrder( (_map->getHeight()*TILE_HEIGHT - _player->getPosition().y) );
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
        //_mobs[spriteMove->getGameObjectId()]->setZOrder(
        _batchNode->reorderChild(_mobs[spriteMove->getGameObjectId()],
            _map->getHeight()*TILE_HEIGHT - spriteMove->getPosition().y - TILE_HEIGHT/4 // DO NOT CHANGE
        );
    }
    // First occurence of a sprite
    else
    {
        TMXLayer *spritesLayer = _map->getTiledMap()->layerNamed("sprites");
        Point mobTilePosition = ccp(
                                spriteMove->getGameObjectId() % _map->getWidth(),
                                _map->getHeight() - spriteMove->getGameObjectId() / _map->getWidth() - 1
                            ); 
        int spriteGID = spritesLayer->tileGIDAt(mobTilePosition);
        if(spriteGID != 0)  // Not empty
        {
            _mobs[spriteMove->getGameObjectId()] = spritesLayer->tileAt(mobTilePosition);
            _batchNode->addChild(_mobs[spriteMove->getGameObjectId()], 0);
            _mobs[spriteMove->getGameObjectId()]->setVertexZ(0);
        }
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
    Bomb *bomb = Bomb::create(_map, _player);
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
    _map->removeChild(bomb);
}

//
void GUIUpdater::updateObstacleDestroy(Backend::GSCObstacleDestroy *obstacleDestroy)
{
    int bombID = (_map->getHeight() - ( obstacleDestroy->getGameObjectId() / _map->getWidth() ) - 1) 
                * _map->getWidth()
                + obstacleDestroy->getGameObjectId() % _map->getWidth();
    _obstacles[bombID]->setVisible(false);
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
