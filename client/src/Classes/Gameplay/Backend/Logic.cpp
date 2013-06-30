
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
    unsigned int owner;

    Coordinates epicentrum;

    std::vector<Bomb *> bombsToDestroy;

    for (auto pair : _state->getBombLayer()->getObjects())
    {
        object = pair.second;

        if (object->isExplodable())
        {
            Bomb* bomb =  (Bomb *) object;
            bomb->update(dt);

            if (bomb->isDetonated())
            {
                //_gameStateUpdater->getState()->getObstaclesLayer()->print();

                power = bomb->getPower();
                epicentrum = bomb->getCoords();
                penetration = bomb->getPenetration();
                owner = bomb->getOwnerId();
                
                _gameStateUpdater->spawnExplosion(bomb);
                //_gameStateUpdater->destroyBomb(bomb);
                bombsToDestroy.push_back(bomb);

                penetrationTop = penetration;
                penetrationBottom = penetration;
                penetrationLeft = penetration;
                penetrationRight = penetration;

                for (int i = 0; i < power; i++)
                {
                    _gameStateUpdater->makeBombImpact(
                            owner,
                            &penetrationTop,
                            epicentrum.x,
                            epicentrum.y + i + 1
                    );
                    _gameStateUpdater->makeBombImpact(
                            owner,
                            &penetrationBottom,
                            epicentrum.x,
                            epicentrum.y - i - 1
                    );
                    _gameStateUpdater->makeBombImpact(
                            owner,
                            &penetrationRight,
                            epicentrum.x + i + 1,
                            epicentrum.y
                    );
                    _gameStateUpdater->makeBombImpact(
                            owner,
                            &penetrationLeft,
                            epicentrum.x - i - 1,
                            epicentrum.y
                    );
                }

                //_gameStateUpdater->getState()->getObstaclesLayer()->print();
            }
        }

    }

    for (auto bomb : bombsToDestroy)
    {
        _gameStateUpdater->destroyBomb(bomb);
    }

    auto spriteLayer = _state->getSpriteLayer();
    auto portalLayer = _state->getPortalLayer();
    auto portalExitLayer = _state->getPortalExitLayer();
    auto effectLayer = _state->getEffectLayer();

    std::vector<Effect *> effectsToDestroy;

    for (auto pair : spriteLayer->getObjects())
    {
        Sprite *sprite = (Sprite *) pair.second;
        sprite->update(dt);

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
                effectsToDestroy.push_back(effect);
            }
        }

        for (auto effect : effectsToDestroy)
        {
            _gameStateUpdater->destroyEffect(effect);
        }
    }

    _gameStateUpdater->updateGrid();
}

void Logic::setControlledSprite(unsigned int spriteId)
{
    _controlledSprite = (Sprite *) _state->getSpriteLayer()->getObject(spriteId);
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
    bool ok = _gameStateUpdater->spawnBomb((Sprite *) _state->getSpriteLayer()->getObject(spriteId));
    //_gameStateUpdater->getState()->getBombLayer()->print();
    return ok;
}
