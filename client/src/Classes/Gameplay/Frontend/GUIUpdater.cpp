#include "GUIUpdater.h"

using namespace Bomber::Frontend;

//
GUIUpdater *GUIUpdater::getInstance()
{
    static GUIUpdater instance;
    return &instance;
}

//
void GUIUpdater::init( Map* map, Human* player, CCLayer* layer)
{
    _map = map;
    _player = player;
    _layer = layer;
}

//
void GUIUpdater::update(CCPoint playerPosition)
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
    return;
}


//
void GUIUpdater::updateSpriteTeleport(Backend::GSCSpriteTeleport *spriteTeleport, CCPoint playerPosition)
{
    //std::cout << spriteTeleport->getGameObjectId() << "\n";
    CCPoint teleportPosition = ccp( spriteTeleport->getPosition().x, spriteTeleport->getPosition().y);
    _player->setPosition(teleportPosition);
    _map->addToPosition(ccpSub(playerPosition, teleportPosition));
    return;
}

//
void GUIUpdater::updateBombSpawn(Backend::GSCBombSpawn *bombSpawn)
{
    CCPoint bombSpawnPosition = ccp( bombSpawn->getPosition().x, bombSpawn->getPosition().y);
    CCPoint tilemapPosition = _player->getTilemapPosition(); // WARNING
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
    CCTMXLayer *obstaclesLayer = _map->getTiledMap()->layerNamed("obstacles");
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
    CCPoint epicentrum = ccp(explosionSpawn->getEpicentrum().x, explosionSpawn->getEpicentrum().y);
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