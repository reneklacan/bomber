
#include <stdio.h>

#include "Statistics.h"

using namespace Bomber::Backend;

Statistics::Statistics()
{
    this->reset();
}

void Statistics::reset()
{
    _bombSpawns = 0;
    _totalKills = 0;
    _kills.clear();
    _totalEffects = 0;
    _effects.clear();
    _totalObstacles = 0;
    _obstacles.clear();
}

void Statistics::increaseBombSpawns()
{
    _bombSpawns += 1;
}

void Statistics::increaseKills(const char *name)
{
    _totalKills += 1;
    _kills[name] += 1;
}

void Statistics::increaseEffects(const char *name)
{
    _totalEffects += 1;
    _effects[name] += 1;
}

void Statistics::increaseObstacles(const char *name)
{
    _totalObstacles += 1;
    _obstacles[name] += 1;
}

void Statistics::print()
{
    printf("----------\n");
    printf("Bomb spawns: %d\n", _bombSpawns);
    printf("Total kills: %d\n", _totalKills);
    printf("Kills:\n");
    for (auto pair : _kills)
    {
        printf(" - %s: %d\n", pair.first, pair.second);
    }
    printf("Total effects: %d\n", _totalEffects);
    printf("Effects:\n");
    for (auto pair : _effects)
    {
        printf(" - %s: %d\n", pair.first, pair.second);
    }
    printf("Total obstacles destroyed: %d\n", _totalObstacles);
    printf("Obstacles destroyed:\n");
    for (auto pair : _obstacles)
    {
        printf(" - %s: %d\n", pair.first, pair.second);
    }
    printf("----------\n");
}
