
#include "GameStateUpdater.h"

using namespace Bomber::Backend;

GameStateUpdater::GameStateUpdater()
{
    _uniqueId = 1;
}

void GameStateUpdater::updateGrid()
{
    _state->getSpriteLayer()->updateGrid();
}

bool GameStateUpdater::moveSprite(GameObject *sprite, Position position)
{
    this->logSpriteMove(sprite, sprite->getPosition(), position);
    sprite->setPosition(position);
}

bool GameStateUpdater::teleportSprite(GameObject *sprite, Position position)
{
    this->logSpriteTeleport(sprite, position);
    sprite->setPosition(position);
}

bool GameStateUpdater::spawnBomb(GameObject *owner)
{
    if (!owner->isBombPotent())
    {
        return false;
    }

    if (_state->getObstaclesLayer()->getObjectsAtCoords(owner->getCoords()).size())
    {
        printf("bomb spawn failed, tile occupied by obstacle\n");
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
    delete bomb;
}

void GameStateUpdater::spawnExplosion(ExplodableObject *explObj)
{
    this->logExplosionSpawn(explObj);
}

void GameStateUpdater::makeBombImpact(int *penetration, unsigned int x, unsigned int y)
{
    if (!(*penetration))
        return;

    auto objects = _state->getObstaclesLayer()->getObjectsAtCoords(x, y);

    for (auto object : objects)
    {
        if (!(*penetration))
            return;

        Obstacle *obstacle = (Obstacle *) object;

        if (!obstacle->getToughness())
            continue;

        (*penetration)--;

        if (obstacle->decreaseToughness())
            continue;

        _state->getObstaclesLayer()->removeObject(object);

        this->logObstacleDestroy(obstacle);
    }
}

void GameStateUpdater::updateSpriteAttributes(Sprite *sprite, Effect *effect)
{
    effect->applyToSprite(sprite);
    this->logSpriteAttributesUpdate(sprite, effect);
}

void GameStateUpdater::destroyEffect(Effect *effect)
{
    _state->getEffectLayer()->removeObject(effect);
    this->logEffectDestroy(effect);
}

void GameStateUpdater::logSpriteMove(GameObject *sprite, Position &from, Position &to)
{
    //printf("logSpriteMove\n"); // spam
    GSCSpriteMove *change = new GSCSpriteMove();
    change->update(from, to);
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void GameStateUpdater::logSpriteTeleport(GameObject *sprite, Position &to)
{
    printf("logSpriteTeleport\n");
    GSCSpriteTeleport *change = new GSCSpriteTeleport();
    change->update(to);
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
    change->setGameObjectId(bomb->getId());
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

void GameStateUpdater::logObstacleDestroy(Obstacle *obstacle)
{
    printf("logObstacleDestroy\n");
    GSCObstacleDestroy* change = new GSCObstacleDestroy();
    change->update(
            obstacle->getCoords()
    );
    change->setGameObjectId(obstacle->getId());
    _state->addChange(change);
}

void GameStateUpdater::logSpriteAttributesUpdate(Sprite *sprite, Effect *effect)
{
    printf("logSpriteAttributesUpdate\n");
    GSCSpriteAttrUpdate * change = new GSCSpriteAttrUpdate();
    change->update(
            effect->getType()
    );
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void GameStateUpdater::logEffectDestroy(Effect *effect)
{
    printf("logEffectDestroy\n");
    GSCEffectDestroy* change = new GSCEffectDestroy();
    change->update(
            effect->getCoords()
    );
    change->setGameObjectId(effect->getId());
    _state->addChange(change);
}
