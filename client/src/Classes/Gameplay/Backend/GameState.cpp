
#include "GameState.h"

using namespace Bomber::Backend;

GameState::GameState()
{
    _lastChangeId = 0;

    int _width = 10;
    int _height = 10;

    _spriteLayer = new GameStateLayer(_width, _height);
    _obstacleLayer = new GameStateLayer(_width, _height);
    _portalLayer = new GameStateLayer(_width, _height);
    _portalExitLayer = new GameStateLayer(_width, _height);
    _specialLayer = new GameStateLayer(_width, _height);
    _bombLayer = new GameStateLayer(_width, _height);

    GameStateLayer *layers[] = {
        _spriteLayer,
        _obstacleLayer,
        _portalLayer,
        _portalExitLayer,
        _specialLayer,
        _bombLayer
    };

    _allLayers.insert(
            _allLayers.begin(),
            layers,
            layers + sizeof(layers)/sizeof(layers[0])
    );
}

GameState::~GameState()
{

}

std::vector<GameStateChange *> GameState::getChangesFromId(unsigned int id)
{
    std::vector<GameStateChange *> changes;

    for (int i = id; i < _lastChangeId; i++)
    {
        changes.push_back(_changes[i]);
    }

    return changes;
}

void GameState::addChange(GameStateChange *change)
{
    _lastChangeId += 1;
    _changes.push_back(change);
}

void GameState::gatherChanges()
{
    GameStateChange *change;

    for (GameStateLayer *layer : _allLayers)
    {
        while (!layer->getChanges().empty())
        {
            while ((change = layer->popChange()) != nullptr)
            {
                this->addChange(change);
            }
        }
    }
}
