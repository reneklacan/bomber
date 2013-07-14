
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
    _levelStatistics = new Statistics();
    _gameStatistics = new Statistics();
    _relevantSpriteId = 0;
}

void StatisticsUpdater::resetLevelStatistics()
{
    _levelStatistics->reset();
}

void StatisticsUpdater::updateMobsAlive(int mobsAlive)
{
    _levelStatistics->setMobsAlive(mobsAlive);
}

void StatisticsUpdater::updateKillStreaks(int mobKills)
{
    if (mobKills <= _gameStatistics->getKillStreaks())
        return;

    _gameStatistics->setKillStreaks(mobKills);

    AchievementContainer::getInstance()->checkAll(_gameStatistics); // TODO: check only related groups
}

void StatisticsUpdater::bombSpawned(unsigned int ownerId, BBomb *bomb)
{
    if (ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseBombSpawns();
    _gameStatistics->increaseBombSpawns();

    AchievementContainer::getInstance()->checkAll(_gameStatistics); // TODO: check only related groups
}

void StatisticsUpdater::effectTaken(unsigned int ownerId, Effect *effect)
{
    if (ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseEffects(effect->getName());
    _gameStatistics->increaseEffects(effect->getName());

    AchievementContainer::getInstance()->checkAll(_gameStatistics); // TODO: check only related groups
}

void StatisticsUpdater::monsterKilled(unsigned int ownerId, Sprite *monster)
{
    if (ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseKills(monster->getName());
    _gameStatistics->increaseKills(monster->getName());

    AchievementContainer::getInstance()->checkAll(_gameStatistics); // TODO: check only related groups
}

void StatisticsUpdater::obstacleDestroyed(unsigned int ownerId, Obstacle *obstacle)
{
    if (ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseObstacles(obstacle->getName());
    _gameStatistics->increaseObstacles(obstacle->getName());

    AchievementContainer::getInstance()->checkAll(_gameStatistics); // TODO: check only related groups
}

void StatisticsUpdater::teleportUsed(unsigned int ownerId)
{
    if (ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseTeleportUses();
    _gameStatistics->increaseTeleportUses();

    AchievementContainer::getInstance()->checkAll(_gameStatistics); // TODO: check only related groups
}

void StatisticsUpdater::leverUsed(unsigned int ownerId)
{
    if (ownerId != _relevantSpriteId)
        return;

    _levelStatistics->increaseLeverUses();
    _gameStatistics->increaseLeverUses();

    AchievementContainer::getInstance()->checkAll(_gameStatistics); // TODO: check only related groups
}
