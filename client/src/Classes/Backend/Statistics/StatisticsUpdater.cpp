
#include "StatisticsUpdater.h"
#include "AchievementContainer.h"

using namespace Bomber::Backend;

StatisticsUpdater *StatisticsUpdater::_instance = nullptr;

StatisticsUpdater *StatisticsUpdater::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new StatisticsUpdater();
    }
    return _instance;
}

StatisticsUpdater::StatisticsUpdater()
{
    _enabled = true;
    _levelStatistics = new Statistics();
    _gameStatistics = new Statistics();
    _relevantSpriteId = 0;
}

void StatisticsUpdater::resetLevelStatistics()
{
    if (!_enabled)
        return;

    _levelStatistics->reset();
}

void StatisticsUpdater::updateMobsAlive(int mobsAlive)
{
    _levelStatistics->setMobsAlive(mobsAlive);
}

void StatisticsUpdater::updateKillStreaks(unsigned int mobKills)
{
    if (!_enabled)
        return;

    if (mobKills <= _gameStatistics->getKillStreaks())
        return;

    _gameStatistics->setKillStreaks(mobKills);
    
    AchievementContainer::getInstance()->checkType(KILL_STREAKS, _gameStatistics);
}

void StatisticsUpdater::bombSpawned(unsigned int ownerId, Bomb *bomb)
{
    if (!_enabled || ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseBombSpawns();
    _gameStatistics->increaseBombSpawns();
    
    AchievementContainer::getInstance()->checkType(BOMBS, _gameStatistics);
}

void StatisticsUpdater::effectTaken(unsigned int ownerId, Effect *effect)
{
    if (!_enabled || ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseEffects(effect->getName());
    _gameStatistics->increaseEffects(effect->getName());
    
    AchievementContainer::getInstance()->checkType(EFFECTS, _gameStatistics);
}

void StatisticsUpdater::monsterKilled(unsigned int ownerId, Sprite *monster)
{
    if (!_enabled || ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseKills(monster->getName());
    _gameStatistics->increaseKills(monster->getName());
    
    AchievementContainer::getInstance()->checkType(KILLS, _gameStatistics);
}

void StatisticsUpdater::obstacleDestroyed(unsigned int ownerId, Obstacle *obstacle)
{
    if (!_enabled || ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseObstacles(obstacle->getName());
    _gameStatistics->increaseObstacles(obstacle->getName());
    
    AchievementContainer::getInstance()->checkType(OBSTACLES, _gameStatistics);
}

void StatisticsUpdater::teleportUsed(unsigned int ownerId)
{
    if (!_enabled || ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseTeleportUses();
    _gameStatistics->increaseTeleportUses();
    
    AchievementContainer::getInstance()->checkType(TELEPORTS, _gameStatistics);
}

void StatisticsUpdater::leverUsed(unsigned int ownerId)
{
    if (!_enabled || ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseLeverUses();
    _gameStatistics->increaseLeverUses();
    
    AchievementContainer::getInstance()->checkType(LEVERS, _gameStatistics);
}
