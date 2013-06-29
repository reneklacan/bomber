
#include <iostream>

#include "Logic.h"
#include "Obstacle.h"

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

    int ix, iy, power,
        penetration, penetrationTop, penetrationBottom,
        penetrationRight, penetrationLeft;

    Coordinates epicentrum;

    for (auto layer : _state->getAllLayers())
    {
        for (auto pair : layer->getObjects())
        {
            object = pair.second;
            object->update(dt);

            if (object->isExplodable())
            {
                Bomb* bomb =  (Bomb *) object;
                if (bomb->isDetonated())
                {
                    _gameStateUpdater->getState()->getObstaclesLayer()->print();
                    
                    _gameStateUpdater->destroyBomb(bomb);
                    _gameStateUpdater->spawnExplosion(bomb);

                    power = bomb->getPower();
                    epicentrum = bomb->getCoords();
                    penetration = bomb->getPenetration();

                    penetrationTop = penetration;
                    penetrationBottom = penetration;
                    penetrationLeft = penetration;
                    penetrationRight = penetration;

                    ix = epicentrum.x;
                    iy = epicentrum.y;

                    for (int i = 0; i < power; i++)
                    {
                        printf("--top p=%d\n", penetrationTop);
                        _gameStateUpdater->makeBombImpact(
                                &penetrationTop,
                                epicentrum.x,
                                epicentrum.y + i + 1
                        );
                        printf("--bottom p=%d\n", penetrationBottom);
                        _gameStateUpdater->makeBombImpact(
                                &penetrationBottom,
                                epicentrum.x,
                                epicentrum.y - i - 1
                        );
                        printf("--right p=%d\n", penetrationRight);
                        _gameStateUpdater->makeBombImpact(
                                &penetrationRight,
                                epicentrum.x + i + 1,
                                epicentrum.y
                        );
                        printf("--left p=%d\n", penetrationLeft);
                        _gameStateUpdater->makeBombImpact(
                                &penetrationLeft,
                                epicentrum.x - i - 1,
                                epicentrum.y
                        );
                    }

                    _gameStateUpdater->getState()->getObstaclesLayer()->print();
                }
            }

        }
    }

    _gameStateUpdater->updateGrid();
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

    bool ok = _gameStateUpdater->spawnBomb(_controlledSprite);
    //_gameStateUpdater->getState()->getBombLayer()->print();
    return ok;
}

bool Logic::spawnBomb(unsigned int spriteId)
{
    bool ok = _gameStateUpdater->spawnBomb(_state->getSpriteLayer()->getObject(spriteId));
    //_gameStateUpdater->getState()->getBombLayer()->print();
    return ok;
}
