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
                _map->addChild(_obstacles[_map->getWidth() * iy + ix], 1);
                _obstacles[_map->getWidth() * iy + ix]->setZOrder(iy*TILE_HEIGHT+5); // DO NOT CHANGE or you will shit bricks
                _obstacles[_map->getWidth() * iy + ix]->setVertexZ(0.00001); // DO NOT CHANGE or you will shit bricks
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

    //_obstacles[5*_map->getWidth()+5]->setZOrder(5*TILE_HEIGHT);
    //_obstacles[5*_map->getWidth()+5]->setVertexZ(5);
    //_obstacles[5*_map->getWidth()+5]->setPosition(_obstacles[5*_map->getWidth()+5]->getPosition());

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
        _mobs[spriteMove->getGameObjectId()]->setVertexZ( _player->getVertexZ() - 0.0001 ); // DO NOT CHANGE or you will shit bricks
        _mobs[spriteMove->getGameObjectId()]->setZOrder( 
            _map->getHeight()*TILE_HEIGHT - spriteMove->getPosition().y - TILE_HEIGHT/4 // DO NOT CHANGE or you will shit bricks
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
            _map->addChild(_mobs[spriteMove->getGameObjectId()], 0);
            //_mobs[spriteMove->getGameObjectId()] = Human::create(_map, 1);
            //_mobs[spriteMove->getGameObjectId()]->retain();
            //_map->addChild(_mobs[spriteMove->getGameObjectId()], 0);
            //_mobs[spriteMove->getGameObjectId()]->setAnchorPoint(ccp(-0.20f, -0.1f));
            //_mobs[spriteMove->getGameObjectId()]->setPosition(mobTilePosition);
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
    TMXLayer *obstaclesLayer = _map->getTiledMap()->layerNamed("obstacles");
    obstaclesLayer->removeTileAt(
        ccp( 
            obstacleDestroy->getGameObjectId() % _map->getWidth(), 
            _map->getHeight() - ( obstacleDestroy->getGameObjectId() / _map->getWidth() ) - 1
        )
    );
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
    explosion->setVertexZ(_layer->getVertexZ());
    _map->addChild(explosion, 1);
    return;
}