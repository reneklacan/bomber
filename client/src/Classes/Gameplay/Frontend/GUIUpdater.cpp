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
    //std::cout << spriteMove->getGameObjectId() << "\n";
    if(spriteMove->getGameObjectId() == _player->getID())
    {
        // Do nothing
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
        }
    }
    //std::cout << spriteMove->getPosition().x << " " << spriteMove->getPosition().y << "\n";

    /*for(int i = 0; i < _map->getWidth(); i++)
    {
        for(int j = 0; j < _map->getHeight(); j++)
        {
            std::cout << "[" << i << ", " << j << "]: " << spritesLayer->tileGIDAt( ccp( i, j ) ) << "\n";
        }
    }*/

    return;
}


//
void GUIUpdater::updateSpriteTeleport(Backend::GSCSpriteTeleport *spriteTeleport, Point playerPosition)
{
    Point teleportPosition = ccp( spriteTeleport->getPosition().x, spriteTeleport->getPosition().y);
    _player->setPosition(teleportPosition);
    _map->addToPosition(ccpSub(playerPosition, teleportPosition));
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