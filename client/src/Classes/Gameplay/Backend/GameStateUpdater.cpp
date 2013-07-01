
#include "GameStateUpdater.h"
#include "Statistics/StatisticsUpdater.h"

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
    sprite->setPosition(position);
    this->logSpriteMove(sprite);
}

bool GameStateUpdater::teleportSprite(GameObject *sprite, Position position)
{
    this->logSpriteTeleport(sprite, position);
    sprite->setPosition(position);
}

bool GameStateUpdater::spawnBomb(Sprite *owner)
{
    if (!owner->isBombPotent())
    {
        return false;
    }

    if (_state->getObstacleLayer()->getObjectsAtCoords(owner->getCoords()).size())
    {
        printf("bomb spawn failed, tile occupied by obstacle\n");
        return false;
    }

    auto *bombLayer = _state->getBombLayer();

    Bomb *bomb = new Bomb();
    bomb->configure(owner);
    bomb->setId(this->getUniqueId());

    bombLayer->addObject(bomb);

    StatisticsUpdater::getInstance()->bombSpawned(owner->getId(), bomb);
    this->logBombSpawn(bomb);

    return true;
}

void GameStateUpdater::destroyBomb(Bomb *bomb)
{
    _state->getBombLayer()->removeObject(bomb);
    this->logBombDestroy(bomb);
    //delete bomb;
}

void GameStateUpdater::spawnExplosion(ExplodableObject *explObj, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength)
{
    this->logExplosionSpawn(
            explObj,
            topArmLength,
            bottomArmLength,
            leftArmLength,
            rightArmLength
    );
}

void GameStateUpdater::makeBombImpact(unsigned int ownerId, int *penetration, unsigned int x, unsigned int y)
{
    if (!(*penetration))
        return;

    auto objects = _state->getObstacleLayer()->getObjectsAtCoords(x, y);

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

        _state->getObstacleLayer()->removeObject(object);

        StatisticsUpdater::getInstance()->obstacleDestroyed(ownerId, obstacle);
        this->logObstacleDestroy(obstacle);
    }
}

void GameStateUpdater::updateSpriteAttributes(Sprite *sprite, Effect *effect)
{
    effect->applyToSprite(sprite);
    StatisticsUpdater::getInstance()->effectTaken(sprite->getId(), effect);
    this->logSpriteAttributesUpdate(sprite, effect);
}

void GameStateUpdater::destroyEffect(Effect *effect)
{
    _state->getEffectLayer()->removeObject(effect);
    this->logEffectDestroy(effect);
}

void GameStateUpdater::updateAchievements()
{
    if (!AchievementContainer::getInstance()->isNewQueueEmpty())
    {
        for (Achievement *achievement : AchievementContainer::getInstance()->getNewUnlocked())
        {
            printf("----------!\n");
            printf("Achievement unlocked!\n");
            printf("%s!\n", achievement->getTitle());
            printf(" - %s!\n", achievement->getDescription());
            printf("----------!\n");

            this->logAchievementUnlocked(achievement);
        }
    }
}

void GameStateUpdater::logSpriteMove(GameObject *sprite)
{
    //printf("logSpriteMove\n"); // spam
    GSCSpriteMove *change = new GSCSpriteMove();
    change->update(sprite->getPosition());
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

void GameStateUpdater::logExplosionSpawn(ExplodableObject *explObj, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength)
{
    printf("logExplosionSpawn\n");
    GSCExplosionSpawn* change = new GSCExplosionSpawn();
    change->update(
            explObj->getOwnerId(),
            topArmLength,
            bottomArmLength,
            leftArmLength,
            rightArmLength
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

void GameStateUpdater::logAchievementUnlocked(Achievement *achievement)
{
    printf("logAchievementUnlocked\n");
    GSCAchievementUnlocked* change = new GSCAchievementUnlocked();
    change->update(
            achievement->getTitle(),
            achievement->getDescription()
    );
    change->setGameObjectId(0);
    _state->addChange(change);
}
