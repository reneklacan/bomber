
#include "GameStateUpdater.h"
#include "../Statistics/StatisticsUpdater.h"
#include "../../Constants.h"
#include "../../Common/Cache/ObjectCache.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

GameStateUpdater::GameStateUpdater()
:_uniqueId(1)
{

}

void GameStateUpdater::resetState()
{
    _state->reset();
}

void GameStateUpdater::resetLevel()
{
    this->logLevelReset();
    StatisticsUpdater::getInstance()->resetLevelStatistics();
}

void GameStateUpdater::updateSpriteGrid()
{
    _state->getSpriteLayer()->updateGrid();
}

void GameStateUpdater::moveSprite(Sprite *sprite, Position position)
{
    if (sprite == nullptr)
    {
        printf("GameStateUpdater::moveSprite - sprite = null\n");
        return;
    }

    sprite->setPosition(position);
    this->logSpriteMove(sprite);
}

void GameStateUpdater::teleportSprite(Sprite *sprite, Position position)
{
    sprite->setPosition(position);
    StatisticsUpdater::getInstance()->teleportUsed(sprite->getId());
    this->logSpriteTeleport(sprite, position);
}

void GameStateUpdater::spawnSprite(unsigned int spriteGid, Coordinates coords)
{
    Sprite *sprite = Sprite::getInstanceByGid(spriteGid);
    sprite->setId(coords.y*_state->getWidth() + coords.x);
    sprite->setPosition(coords.x*TILE_WIDTH, coords.y*TILE_HEIGHT);
    sprite->setSize(TILE_WIDTH, TILE_HEIGHT);

    _state->getSpriteLayer()->addObject(sprite);

    this->logSpriteSpawn(sprite);
}

void GameStateUpdater::spawnBomb(Sprite *owner)
{
    auto *bombLayer = _state->getBombLayer();
    
    //Bomb *bomb = new Bomb();
    Bomb *bomb = (Bomb *) ObjectCache::getInstance()->getObject(COT_BOMB);
    bomb->configure(owner);
    bomb->setId(this->getUniqueId());

    printf("bomb id = %d\n", bomb->getId());

    bombLayer->addObject(bomb);

    StatisticsUpdater::getInstance()->bombSpawned(owner->getId(), bomb);
    this->logBombSpawn(bomb);
}

void GameStateUpdater::spawnExplosion(Bomb *bomb, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength)
{
    this->logExplosionSpawn(
            bomb,
            topArmLength,
            bottomArmLength,
            leftArmLength,
            rightArmLength
    );
}

void GameStateUpdater::spawnObstacle(unsigned int obstacleGid, Coordinates coords, unsigned int spawnerId)
{
    Obstacle *obstacle = Obstacle::getInstanceByGid(obstacleGid);
    obstacle->setId(coords.y*_state->getWidth() + coords.x);
    obstacle->setPosition(coords.x*TILE_WIDTH, coords.y*TILE_HEIGHT);
    obstacle->setSize(TILE_WIDTH, TILE_HEIGHT);

    _state->getObstacleLayer()->addObject(obstacle);
    _state->getObstacleLayer()->updateGrid();

    this->logObstacleSpawn(obstacleGid, obstacle, spawnerId);
}

void GameStateUpdater::spawnEffect(unsigned int effectGid, Coordinates coords)
{
    Effect *effect = Effect::getInstanceByGid(effectGid);
    effect->setId(coords.y*_state->getWidth() + coords.x);
    effect->setPosition(coords.x*TILE_WIDTH, coords.y*TILE_HEIGHT);
    effect->setSize(TILE_WIDTH, TILE_HEIGHT);

    _state->getEffectLayer()->addObject(effect);

    this->logEffectSpawn(effect);
}

void GameStateUpdater::updateSpriteAttributes(Sprite *sprite, Effect *effect)
{
    effect->applyToSprite(sprite);
    StatisticsUpdater::getInstance()->effectTaken(sprite->getId(), effect);

    if (sprite->getAttributes()->isDead())
        this->destroySprite(sprite);
    else
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
            /*
            printf("----------!\n");
            printf("Achievement unlocked!\n");
            printf("%s!\n", achievement->getTitle());
            printf(" - %s!\n", achievement->getDescription());
            printf("----------!\n");
            */

            this->logAchievementUnlocked(achievement);
        }
    }

    if (_state->getGoalReached())
        return;

    bool goalComplete = true;

    // currently all goals should be reached to complete the level
    // TODO: or operator
    for (auto condition : _state->getGoalConditions())
    {
        auto type = condition.first;
        auto value = condition.second;

        if (type == CONDITION_MOBS_ALIVE)
        {
            if (StatisticsUpdater::getInstance()->getLevelStatistics()->getMobsAlive() != value)
                goto goal_failed;
        }
        else if (type == CONDITION_LEVEL_KEYS)
        {
            int spritesChecked = 0;

            for (auto sprite : _state->getSpriteLayer()->getObjects())
            {
                if (sprite->isAI())
                    continue;

                spritesChecked++;

                if (sprite->getAttributes()->getLevelKeys() != value)
                    goto goal_failed;
            }

            if (spritesChecked == 0)
                goto goal_failed;
        }
        else
        {
            printf("unknown condition type '%d'", type);
            goalComplete = false;
        }
    }

goal_complete:

    if (goalComplete)
    {
        // allow player proceed to the next level
        this->logLevelFinish();
        _state->setGoalReached(true);
    }

goal_failed:

    return;
}

void GameStateUpdater::pushBlock(Coordinates from, Coordinates to)
{
    this->logBlockPush(from, to);
}

void GameStateUpdater::switchLeverOn(GameObject *lever, unsigned int causerId)
{
    StatisticsUpdater::getInstance()->leverUsed(causerId);
    this->logLeverSwitchOn(lever);
}

void GameStateUpdater::switchLeverOff(GameObject *lever, unsigned int causerId)
{
    StatisticsUpdater::getInstance()->leverUsed(causerId);
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

    ObjectCache::getInstance()->returnObject(sprite);

    //TEST
    this->logDialogBubble();
}

void GameStateUpdater::destroyBomb(Bomb *bomb)
{
    _state->getBombLayer()->removeObject(bomb);
    this->logBombDestroy(bomb);
    //delete bomb;
    ObjectCache::getInstance()->returnObject(bomb);
}

void GameStateUpdater::destroyEffect(Effect *effect)
{
    _state->getEffectLayer()->removeObject(effect);
    this->logEffectDestroy(effect);
    ObjectCache::getInstance()->returnObject(effect);
}

void GameStateUpdater::destroyObstacle(Obstacle *obstacle, unsigned int destroyerId)
{
    StatisticsUpdater::getInstance()->obstacleDestroyed(destroyerId, obstacle);
    _state->getObstacleLayer()->removeObject(obstacle);
    this->logObstacleDestroy(obstacle);
    ObjectCache::getInstance()->returnObject(obstacle);
}

void GameStateUpdater::logSpriteMove(Sprite *sprite)
{
    //printf("logSpriteMove\n"); // spam
    GSCSpriteMove *change = new GSCSpriteMove();
    change->update(sprite->getPosition());
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void GameStateUpdater::logBombMove(Bomb *bomb)
{
    //printf("logBombMove\n"); // spam
    GSCBombMove *change = new GSCBombMove();
    change->update(bomb->getPosition());
    change->setGameObjectId(bomb->getId());
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

void GameStateUpdater::logSpriteSpawn(Sprite *sprite)
{
    printf("logSpriteSpawn\n");
    GSCSpriteSpawn *change = new GSCSpriteSpawn();
    change->update(
        sprite->getGid(),
        sprite->getCoords()
    );
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

void GameStateUpdater::logExplosionSpawn(Bomb *bomb, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength)
{
    printf("logExplosionSpawn\n");
    GSCExplosionSpawn* change = new GSCExplosionSpawn();
    change->update(
        bomb->getOwnerId(),
        bomb->getCollisionRect().getCenterPosition(),
        topArmLength,
        bottomArmLength,
        leftArmLength,
        rightArmLength
    );
    change->setGameObjectId(bomb->getId());
    _state->addChange(change);
}

void GameStateUpdater::logObstacleSpawn(unsigned int obstacleGid, Obstacle *obstacle, unsigned int spawnerId)
{
    printf("logObstacleSpawn\n");
    GSCObstacleSpawn *change = new GSCObstacleSpawn();
    change->update(
        obstacleGid,
        obstacle->getCoords(),
        spawnerId
    );
    change->setGameObjectId(obstacle->getId());
    _state->addChange(change);
}

void GameStateUpdater::logEffectSpawn(Effect *effect)
{
    printf("logEffectSpawn\n");
    GSCEffectSpawn *change = new GSCEffectSpawn();
    change->update(
        effect->getGid(),
        effect->getCoords()
    );
    change->setGameObjectId(effect->getId());
    _state->addChange(change);
}

void GameStateUpdater::logObstacleDestroy(Obstacle *obstacle)
{
    printf("logObstacleDestroy\n");
    GSCObstacleDestroy *change = new GSCObstacleDestroy();
    change->update(obstacle->getCoords());
    change->setGameObjectId(obstacle->getId());
    _state->addChange(change);
}

void GameStateUpdater::logSpriteAttributesUpdate(Sprite *sprite, Effect *effect)
{
    printf("logSpriteAttributesUpdate\n");
    GSCSpriteAttrUpdate *change = new GSCSpriteAttrUpdate();
    change->update(
        effect->getGid(),
        effect->getType()
    );
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void GameStateUpdater::logBlockPush(Coordinates from, Coordinates to)
{
    printf("logBlockPush\n");
    GSCBlockPush *change = new GSCBlockPush();
    change->update(from, to);
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
    GSCLeverSwitchOff *change = new GSCLeverSwitchOff();
    change->setGameObjectId(lever->getId());
    _state->addChange(change);
}

void GameStateUpdater::logEffectDestroy(Effect *effect)
{
    printf("logEffectDestroy\n");
    GSCEffectDestroy *change = new GSCEffectDestroy();
    change->update(
        effect->getCoords()
    );
    change->setGameObjectId(effect->getId());
    _state->addChange(change);
}

void GameStateUpdater::logAchievementUnlocked(Achievement *achievement)
{
    printf("logAchievementUnlocked\n");
    GSCAchievementUnlocked *change = new GSCAchievementUnlocked();
    change->update(
        achievement->getTitle(),
        achievement->getDescription()
    );
    change->setGameObjectId(0);
    _state->addChange(change);
}

void GameStateUpdater::logDialogBubble()
{
    printf("logDialogBubble\n");
    GSCDialogBubble *change = new GSCDialogBubble();
    //change->setGameObjectId(sprite->getId());
    change->setTitle("Jesse Pinkman");
    change->setDescription("Yeah Science, Bitch!");
    change->setImage("test_50.png");
    _state->addChange(change);
}

void GameStateUpdater::logLevelFinish()
{   
    printf("logLevelFinish\n");
    GSCLevelFinish *change = new GSCLevelFinish();
    StatisticsUpdater* su = StatisticsUpdater::getInstance();
    change->update(
        su->getLevelStatistics()->getBombSpawns(),
        su->getLevelStatistics()->getTotalKills(),
        su->getLevelStatistics()->getTotalEffects(),
        su->getLevelStatistics()->getTotalObstacles(),
        su->getLevelStatistics()->getTeleportUses(),
        su->getLevelStatistics()->getLeverUses()
    );
    _state->addChange(change);
}

void GameStateUpdater::logLevelReset()
{   
    printf("logLevelReset\n");
    GSCLevelReset *change = new GSCLevelReset();
    _state->addChange(change);
}
