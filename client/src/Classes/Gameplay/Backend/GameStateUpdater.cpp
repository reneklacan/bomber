
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

void GameStateUpdater::moveSprite(Sprite *sprite, Position position)
{
    sprite->setPosition(position);
    this->logSpriteMove(sprite);
}

void GameStateUpdater::teleportSprite(Sprite *sprite, Position position)
{
    this->logSpriteTeleport(sprite, position);
    sprite->setPosition(position);
}

void GameStateUpdater::destroySprite(Sprite *sprite)
{
    this->logSpriteDestroy(sprite);

    _state->getSpriteLayer()->removeObject(sprite);
}

bool GameStateUpdater::spawnBomb(Sprite *owner)
{
    if (!owner->isBombPotent())
    {
        return false;
    }

    if (_state->getObstacleLayer()->getObjectsAtCoords(owner->getCoords()).size() != 0)
    {
        printf("bomb spawn failed, tile occupied by obstacle\n");
        return false;
    }

    if (_state->getBombLayer()->getObjectsAtCoords(owner->getCoords()).size() != 0)
    {
        printf("bomb spawn failed, tile occupied by another bomb\n");
        return false;
    }

    auto *bombLayer = _state->getBombLayer();

    BBomb *bomb = new BBomb();
    bomb->configure(owner);
    bomb->setId(this->getUniqueId());

    bombLayer->addObject(bomb);

    StatisticsUpdater::getInstance()->bombSpawned(owner->getId(), bomb);
    this->logBombSpawn(bomb);

    return true;
}

void GameStateUpdater::destroyBomb(BBomb *bomb)
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

bool GameStateUpdater::makeBombImpact(BBomb *bomb, int *penetration, unsigned int x, unsigned int y)
{
    if (penetration != NULL && !(*penetration))
        return false;

    auto sprites = _state->getSpriteLayer()->getObjectsAtCoords(x, y);

    for (auto sprite : sprites)
    {
        if (!sprite->isAI()) continue; // temporary

        this->logSpriteDamage(sprite, bomb->getDamage());
        sprite->getAttributes()->decreaseHealth(bomb->getDamage());

        if (sprite->getAttributes()->isDead())
        {
            this->destroySprite(sprite);
        }
    }

    if (penetration == NULL)
        return true;

    auto obstacles = _state->getObstacleLayer()->getObjectsAtCoords(x, y);

    if (obstacles.size() == 0)
        return true;

    bool somethingDamaged = false;

    for (auto object : obstacles)
    {
        if (!(*penetration))
            return somethingDamaged;

        Obstacle *obstacle = (Obstacle *) object;

        if (!obstacle->getToughness())
        {
            *penetration = 0;
            continue;
        }

        (*penetration)--;

        if (obstacle->decreaseToughness())
            continue;

        _state->getObstacleLayer()->removeObject(object);

        StatisticsUpdater::getInstance()->obstacleDestroyed(bomb->getOwnerId(), obstacle);
        this->logObstacleDestroy(obstacle);

        somethingDamaged = true;
    }

    return somethingDamaged;
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

void GameStateUpdater::logSpriteMove(Sprite *sprite)
{
    //printf("logSpriteMove\n"); // spam
    GSCSpriteMove *change = new GSCSpriteMove();
    change->update(sprite->getPosition());
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void GameStateUpdater::logSpriteTeleport(Sprite *sprite, Position &to)
{
    printf("logSpriteTeleport\n");
    GSCSpriteTeleport *change = new GSCSpriteTeleport();
    change->update(to);
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void GameStateUpdater::logSpriteDamage(Sprite *sprite, int damage)
{
    printf("logSpriteDamage\n");
    GSCSpriteDamage *change = new GSCSpriteDamage();
    change->setGameObjectId(sprite->getId());
    change->update(damage);
    _state->addChange(change);
}

void GameStateUpdater::logSpriteDestroy(Sprite *sprite)
{
    printf("logSpriteDestroy\n");
    GSCSpriteDestroy *change = new GSCSpriteDestroy();
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void GameStateUpdater::logBombSpawn(BBomb *bomb)
{
    printf("logBombSpawn\n");
    GSCBombSpawn *change = new GSCBombSpawn();
    change->update(bomb->getPosition());
    change->setGameObjectId(bomb->getId());
    _state->addChange(change);
}

void GameStateUpdater::logBombDestroy(BBomb *bomb)
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
            explObj->getCollisionRect().getCenterPosition(),
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
