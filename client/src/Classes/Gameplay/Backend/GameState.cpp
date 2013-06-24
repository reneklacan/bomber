
#include "GameState.h"

using namespace Bomber::Backend;

GameState::GameState()
{
    _lastChangeId = 0;
}

GameState::~GameState()
{

}

void GameState::addChange(GameStateChange *change)
{
    _lastChangeId += 1;
    _changes.push_back(change);
}
