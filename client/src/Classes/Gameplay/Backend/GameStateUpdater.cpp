
#include "GameStateUpdater.h"
#include "Statistics/StatisticsUpdater.h"
#include "../../Constants.h"

using namespace Bomber::Backend;

GameStateUpdater::GameStateUpdater()
{
    _uniqueId = 1;
}

void GameStateUpdater::resetState()
{
    _state->reset();
}

void GameStateUpdater::updateSpriteGrid()
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
    sprite->setPosition(position);
    this->logSpriteTeleport(sprite, position);
}

void GameStateUpdater::spawnSprite(unsigned int spriteGid, Coordinates coords)
{
    Sprite *sprite = Sprite::getInstanceByGid(spriteGid);
    sprite->setId(coords.y*_state->getWidth() + coords.x);
    sprite->setPosition(coords.x*TILE_WIDTH, coords.y*TILE_HEIGHT);
    sprite->setSize(TILE_WIDTH, TILE_HEIGHT);

    _state->getSpriteLayer()->addObject(sprite);

    this->logSpriteSpawn(spriteGid, sprite);
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

void GameStateUpdater::spawnObstacle(unsigned int obstacleGid, Coordinates coords, unsigned int spawnerId)
{
    Obstacle *obstacle = new Obstacle();
    obstacle->setId(coords.y*_state->getWidth() + coords.x);
    obstacle->setPosition(coords.x*TILE_WIDTH, coords.y*TILE_HEIGHT);
    obstacle->setSize(TILE_WIDTH, TILE_HEIGHT);
    obstacle->configureFromGid(obstacleGid);

    _state->getObstacleLayer()->addObject(obstacle);
    _state->getObstacleLayer()->updateGrid();

    this->logObstacleSpawn(obstacleGid, obstacle, spawnerId);
}

void GameStateUpdater::spawnEffect(unsigned int effectGid, Coordinates coords)
{
    Effect *effect= Effect::getInstanceByGid(effectGid);
    effect->setId(coords.y*_state->getWidth() + coords.x);
    effect->setPosition(coords.x*TILE_WIDTH, coords.y*TILE_HEIGHT);
    effect->setSize(TILE_WIDTH, TILE_HEIGHT);

    _state->getEffectLayer()->addObject(effect);
    _state->getEffectLayer()->updateGrid();

    this->logEffectSpawn(effectGid, effect);
}

void GameStateUpdater::updateSpriteAttributes(Sprite *sprite, Effect *effect)
{
    effect->applyToSprite(sprite);
    StatisticsUpdater::getInstance()->effectTaken(sprite->getId(), effect);
    this->logSpriteAttributesUpdate(sprite, effect);
}

void GameStateUpdater::update()
{
    int mobsAlive = 0;

    for (auto sprite : _state->getSpriteLayer()->getObjects())
    {
        if (sprite->isAI() && sprite->getAttributes()->isAlive())
        {
            mobsAlive += 1;
        }
    }

    StatisticsUpdater::getInstance()->updateMobsAlive(mobsAlive);

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

    if (_state->getGoalReached())
        return;

    bool goalComplete = true;

    for (auto condition : _state->getGoalConditions())
    {
        auto type = condition.first;
        auto value = condition.second;

        if (type == CONDITION_MOBS_ALIVE)
        {
            if (StatisticsUpdater::getInstance()->getLevelStatistics()->getMobsAlive() != value)
            {
                goalComplete = false;
                break;
            }
        }
        else
        {
            printf("unknown condition type '%d'", type);
            goalComplete = false;
        }
    }

    if (goalComplete)
    {
        // allow player proceed to the next level
        this->logLevelFinish();
        _state->setGoalReached(true);
    }
}

void GameStateUpdater::switchLeverOn(GameObject *lever)
{
    this->logLeverSwitchOn(lever);
}

void GameStateUpdater::switchLeverOff(GameObject *lever)
{
    this->logLeverSwitchOff(lever);
}

void GameStateUpdater::damageSprite(Sprite *sprite, unsigned int causerId, int damage)
{
    this->logSpriteDamage(sprite, damage);
    sprite->getAttributes()->decreaseHealth(damage);

    if (sprite->getAttributes()->isDead())
    {
        StatisticsUpdater::getInstance()->monsterKilled(causerId, sprite);
        this->destroySprite(sprite);
    }
}

void GameStateUpdater::damageObstacle(Obstacle *obstacle, unsigned int destroyerId)
{
    obstacle->decreaseToughness();

    if (obstacle->getToughness() > 0)
        return;

    this->destroyObstacle(obstacle, destroyerId);
}

void GameStateUpdater::destroySprite(Sprite *sprite)
{
    this->logSpriteDestroy(sprite);

    _state->getSpriteLayer()->removeObject(sprite);
}

void GameStateUpdater::destroyBomb(BBomb *bomb)
{
    _state->getBombLayer()->removeObject(bomb);
    this->logBombDestroy(bomb);
    //delete bomb;
}

void GameStateUpdater::destroyEffect(Effect *effect)
{
    _state->getEffectLayer()->removeObject(effect);
    this->logEffectDestroy(effect);
}

void GameStateUpdater::destroyObstacle(Obstacle *obstacle, unsigned int destroyerId)
{
    StatisticsUpdater::getInstance()->obstacleDestroyed(destroyerId, obstacle);
    _state->getObstacleLayer()->removeObject(obstacle);
    this->logObstacleDestroy(obstacle);
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

void GameStateUpdater::logSpriteSpawn(unsigned int spriteGid, Sprite *sprite)
{
    printf("logSpriteSpawn\n");
    GSCSpriteSpawn* change = new GSCSpriteSpawn();
    change->update(
        spriteGid,
        sprite->getCoords()
    );
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

void GameStateUpdater::logObstacleSpawn(unsigned int obstacleGid, Obstacle *obstacle, unsigned int spawnerId)
{
    printf("logObstacleSpawn\n");
    GSCObstacleSpawn* change = new GSCObstacleSpawn();
    change->update(
        obstacleGid,
        obstacle->getCoords(),
        spawnerId
    );
    change->setGameObjectId(obstacle->getId());
    _state->addChange(change);
}

void GameStateUpdater::logEffectSpawn(unsigned int effectGid, Effect *effect)
{
    printf("logEffectSpawn\n");
    GSCEffectSpawn* change = new GSCEffectSpawn();
    change->update(
        effectGid,
        effect->getCoords()
    );
    change->setGameObjectId(effect->getId());
    _state->addChange(change);
}

void GameStateUpdater::logObstacleDestroy(Obstacle *obstacle)
{
    printf("logObstacleDestroy\n");
    GSCObstacleDestroy* change = new GSCObstacleDestroy();
    change->update(obstacle->getCoords());
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

void GameStateUpdater::logLeverSwitchOn(GameObject *lever)
{
    printf("logLeverSwitchOn\n");
    GSCLeverSwitchOn * change = new GSCLeverSwitchOn();
    change->setGameObjectId(lever->getId());
    _state->addChange(change);
}

void GameStateUpdater::logLeverSwitchOff(GameObject *lever)
{
    printf("logLeverSwitchOff\n");
    GSCLeverSwitchOff * change = new GSCLeverSwitchOff();
    change->setGameObjectId(lever->getId());
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

void GameStateUpdater::logLevelFinish()
{   
    printf("logLevelFinish\n");
    GSCLevelFinish *change = new GSCLevelFinish();
    _state->addChange(change);
}