
#include "StatisticsUpdater.h"

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
}

void StatisticsUpdater::resetLevelStatistics()
{
    _levelStatistics->reset();
}

void StatisticsUpdater::bombSpawned(unsigned int ownerId, Bomb *bomb)
{
    _levelStatistics->increaseBombSpawns();
    _gameStatistics->increaseBombSpawns();
   
    _levelStatistics->print();
}

void StatisticsUpdater::effectTaken(unsigned int ownerId, Effect *effect)
{
    _levelStatistics->increaseEffects(effect->getName());
    _gameStatistics->increaseEffects(effect->getName());
}

void StatisticsUpdater::monsterKilled(unsigned int ownerId, Sprite *monster)
{
    _levelStatistics->increaseKills(monster->getName());
    _gameStatistics->increaseKills(monster->getName());
}

void StatisticsUpdater::obstacleDestroyed(unsigned int ownerId, Obstacle *obstacle)
{
    _levelStatistics->increaseObstacles(obstacle->getName());
    _gameStatistics->increaseObstacles(obstacle->getName());

    _levelStatistics->print();
}
