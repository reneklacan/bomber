#include "FStatistics.h"
#include <iostream>

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
	_score = 0;
}

void Statistics::endLevelTimer()
{
	_end = time(0);
	_timer += ( (int)_end - (int)_start );

	countFinalScore();
	return;
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

// Only for test purpose
// TODO create algorithm
void Statistics::countFinalScore()
{
	_score = (int)( (1000 - (int)_timer * 10) +
			 (_achievementUnlocks * 100) +
			 (_takenBuffs * 5) +
			 (_usedLever * 5) +
			 (_killedMonster * 20) -
			 (_bombSpawns * 5)
		   );
}

int Statistics::getFinalScore()
{
	return _score;
}

unsigned int Statistics::getStars()
{
	if(_score < 500)
	{
		return 1; 
	}
	else if(_score < 700)
	{
		return 2;
	}
	else if(_score < 900)
	{
		return 3; 
	}
	else if(_score < 1100)
	{
		return 4; 
	}
	else
	{
		return 5;
	}
}