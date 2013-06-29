
#include "GameStateUpdater.h"

using namespace Bomber::Backend;

GameStateUpdater::GameStateUpdater()
{
    _uniqueId = 1;
}

bool GameStateUpdater::moveSprite(GameObject *sprite, Position position)
{
    this->logSpriteMove(sprite, sprite->getPosition(), position);

    sprite->setPosition(position);
}

bool GameStateUpdater::spawnBomb(GameObject *owner)
{
    if (!owner->isBombPotent())
    {
        return false;
    }

    GameStateLayer *bombLayer = _state->getBombLayer();

    Bomb *bomb = new Bomb();
    bomb->configure(owner);
    bomb->setId(this->getUniqueId());

    bombLayer->addObject(bomb);

    this->logBombSpawn(bomb);

    return true;
}

void GameStateUpdater::destroyBomb(Bomb *bomb)
{
    _state->getBombLayer()->removeObject(bomb);
    this->logBombDestroy(bomb);
}

void GameStateUpdater::spawnExplosion(ExplodableObject *explObj)
{
    this->logExplosionSpawn(explObj);

    // spawn explosion and destroy blocks and kill sprites
}

void GameStateUpdater::logSpriteMove(GameObject *sprite, Position &from, Position &to)
{
    printf("logSpriteMove\n");
    GSCSpriteMove *change = new GSCSpriteMove();
    change->update(from, to);
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void GameStateUpdater::logBombSpawn(Bomb *bomb)
{
    printf("logBombSpawn\n");
    GSCBombSpawn *change = new GSCBombSpawn();
    change->update(bomb->getPosition());
    change->setGameObjectId(bomb->getId());
    _state->addChange(change);
}

void GameStateUpdater::logBombDestroy(Bomb *bomb)
{
    printf("logBombDestroy\n");
    GSCBombDestroy *change = new GSCBombDestroy();
    change->update(bomb->getId());
    change->setGameObjectId(bomb->getOwnerId());
    _state->addChange(change);
}

void GameStateUpdater::logExplosionSpawn(ExplodableObject *explObj)
{
    printf("logExplosionSpawn\n");
    GSCExplosionSpawn* change = new GSCExplosionSpawn();
    change->update(
            explObj->getOwnerId(),
            explObj->getPower(),
            explObj->getPenetration()
    );
    change->setGameObjectId(explObj->getId());
    _state->addChange(change);
}
