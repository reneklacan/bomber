#include "FStatistics.h"

using namespace Bomber::Frontend;

void Statistics::startLevelTimer()
{
	_timer = 0;
	_end = 0;
	_pause = 0;
	_start = time(0);
	_teleportations = 0;
	_bombSpawns = 0;
	_achievementUnlocks = 0;	// reset at retry ?
	_takenBuffs = 0;
	_usedLever = 0;
	_killedMonster = 0;
}

void Statistics::endLevelTimer()
{
	_end = time(0);
	_timer += ( (int)_end - (int)_start );
}

void Statistics::pauseLevelTimer()
{
	_pause = time(0);
}

void Statistics::resumeLevelTimer()
{
	_timer -= ( (int)time(0) - (int)_pause );
}

int Statistics::getLevelTimer()
{
	return _timer;
}