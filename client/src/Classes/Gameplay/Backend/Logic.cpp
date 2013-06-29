
#include <iostream>

#include "Logic.h"

using namespace Bomber::Backend;

Logic *Logic::_instance = nullptr;

Logic *Logic::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Logic();
    }
    return _instance;
}

Logic::Logic()
{
    _controlledSprite = nullptr;
}

void Logic::update(float dt)
{
    GameObject *object;

    for (auto layer : _state->getAllLayers())
    {
        for (auto pair : layer->getObjects())
        {
            object = pair.second;
            object->update(dt);

            if (object->isExplodable())
            {
                ExplodableObject* explObj =  (ExplodableObject *) object;
                if (explObj->isDetonated())
                {
                    layer->removeObject(object);
                    _gameStateUpdater->spawnExplosion(explObj);
                }
            }

        }
    }
}

void Logic::setControlledSprite(unsigned int spriteId)
{
    _controlledSprite = _state->getSpriteLayer()->getObject(spriteId);
}

void Logic::setGameStateUpdater(GameStateUpdater *updater)
{
    _gameStateUpdater = updater;
    _state = updater->getState();
}

bool Logic::moveSprite(Position position)
{
    if (_controlledSprite == nullptr)
    {
        std::cout << "Logic::_controlledSprite is nullptr\n";
        return false;
    }

    return _gameStateUpdater->moveSprite(_controlledSprite, position);
}

bool Logic::moveSprite(unsigned int spriteId, Position position)
{
    return _gameStateUpdater->moveSprite(_state->getSpriteLayer()->getObject(spriteId), position);
}

bool Logic::spawnBomb()
{ 
    if (_controlledSprite == nullptr)
    {
        std::cout << "Logic::_controlledSprite is nullptr\n";
        return false;
    }

    return _gameStateUpdater->spawnBomb(_controlledSprite);
}

bool Logic::spawnBomb(unsigned int spriteId)
{
    return _gameStateUpdater->spawnBomb(_state->getSpriteLayer()->getObject(spriteId));
}
