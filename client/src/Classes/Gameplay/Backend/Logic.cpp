
#include <iostream>

#include "Logic.h"
#include "Obstacle.h"
#include "Portal.h"
#include "Effect.h"

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

    int power,
        penetration, penetrationTop, penetrationBottom,
        penetrationRight, penetrationLeft;

    Coordinates epicentrum;

    for (auto pair : _state->getBombLayer()->getObjects())
    {
        object = pair.second;
        object->update(dt);

        if (object->isExplodable())
        {
            Bomb* bomb =  (Bomb *) object;

            if (bomb->isDetonated())
            {
                //_gameStateUpdater->getState()->getObstaclesLayer()->print();
                
                _gameStateUpdater->destroyBomb(bomb);
                _gameStateUpdater->spawnExplosion(bomb);

                power = bomb->getPower();
                epicentrum = bomb->getCoords();
                penetration = bomb->getPenetration();

                penetrationTop = penetration;
                penetrationBottom = penetration;
                penetrationLeft = penetration;
                penetrationRight = penetration;

                for (int i = 0; i < power; i++)
                {
                    _gameStateUpdater->makeBombImpact(
                            &penetrationTop,
                            epicentrum.x,
                            epicentrum.y + i + 1
                    );
                    _gameStateUpdater->makeBombImpact(
                            &penetrationBottom,
                            epicentrum.x,
                            epicentrum.y - i - 1
                    );
                    _gameStateUpdater->makeBombImpact(
                            &penetrationRight,
                            epicentrum.x + i + 1,
                            epicentrum.y
                    );
                    _gameStateUpdater->makeBombImpact(
                            &penetrationLeft,
                            epicentrum.x - i - 1,
                            epicentrum.y
                    );
                }

                //_gameStateUpdater->getState()->getObstaclesLayer()->print();
            }
        }

    }

    auto spriteLayer = _state->getSpriteLayer();
    auto portalLayer = _state->getPortalLayer();
    auto portalExitLayer = _state->getPortalExitLayer();
    auto effectLayer = _state->getEffectLayer();

    for (auto pair : spriteLayer->getObjects())
    {
        Sprite *sprite = (Sprite *) pair.second;
        auto portals = portalLayer->getObjectsAroundCoords(sprite->getCoords());

        for (auto object : portals)
        {
            Portal *portal = (Portal *) object;
            
            if (sprite->collides(portal))
            {
                auto portalExit = portalExitLayer->getObject(portal->getId());
                _gameStateUpdater->teleportSprite(sprite, portalExit->getPosition());
                break;
            }
        }

        auto effects = effectLayer->getObjectsAroundCoords(sprite->getCoords());

        for (auto object : effects)
        {
            Effect *effect = (Effect *) object;

            if (sprite->collides(effect))
            {
                _gameStateUpdater->updateSpriteAttributes(sprite, effect);
                _gameStateUpdater->destroyEffect(effect);
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
