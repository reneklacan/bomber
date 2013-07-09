
#include <iostream>

#include "Logic.h"
#include "Obstacle.h"
#include "Portal.h"
#include "Effect.h"
#include "AI/AI.h"

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
    int power,
        penetration, penetrationTop, penetrationBottom,
        penetrationRight, penetrationLeft;
        
    unsigned int owner;

    Coordinates epicentrum;

    std::vector<BBomb *> bombsToDestroy;
    std::deque<BBomb *> bombsToDetonate;
    BBomb *bomb;

    for (auto pair : _state->getBombLayer()->getObjects())
    {
        bomb = pair.second;
        bomb->update(dt);

        if (bomb->isDetonated())
        {
            bombsToDetonate.push_back(bomb);
        }
    }

    while (bombsToDetonate.size() > 0)
    {
        //_gameStateUpdater->getState()->getObstaclesLayer()->print();

        bomb = bombsToDetonate.front();
        bombsToDetonate.pop_front();
        bomb->detonate();

        power = bomb->getPower();
        epicentrum = bomb->getCoords();
        penetration = bomb->getPenetration();
        owner = bomb->getOwnerId();
            
        //_gameStateUpdater->destroyBomb(bomb);
        bombsToDestroy.push_back(bomb);

        penetrationTop = penetration;
        penetrationBottom = penetration;
        penetrationLeft = penetration;
        penetrationRight = penetration;

        int *penetrations[4] = {
            &penetrationTop,
            &penetrationBottom,
            &penetrationLeft,
            &penetrationRight
        };

        int armLengths[4] = {0};

        _gameStateUpdater->makeBombImpact(bomb, NULL, epicentrum.x, epicentrum.y);

        for (int i = 0; i < power; i++)
        {
            auto around = epicentrum.getCoordsAround(i + 1);

            for (int j = 0; j < 4; j++)
            {
                auto coords = around[j];

                for (auto bombObject : _state->getBombLayer()->getObjectsAtCoords(coords))
                {
                    if (!bombObject->isDetonated())
                    {
                        bombsToDetonate.push_back(bombObject);
                    }
                }

                if (_gameStateUpdater->makeBombImpact(bomb, penetrations[j], coords.x, coords.y))
                {
                    armLengths[j]++;
                }
            }
        }

        _gameStateUpdater->spawnExplosion(
                bomb,
                armLengths[0], // top
                armLengths[1], // bottom
                armLengths[2], // left
                armLengths[3]  // right
        );

        //_gameStateUpdater->getState()->getObstaclesLayer()->print();
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
        Sprite *sprite = pair.second;
        sprite->update(dt);

        if (sprite->isAI() && sprite->isDirty())
        {
            _gameStateUpdater->logSpriteMove(sprite);
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

        if (sprite->getAttributes()->getPortability() == false)
        {
            continue;
        }

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
    }

    _gameStateUpdater->updateGrid();
    _gameStateUpdater->updateAchievements();

    //_state->getSpriteLayer()->print();
}

void Logic::setControlledSprite(unsigned int spriteId)
{
    _controlledSprite = (Sprite *) _state->getSpriteLayer()->getObject(spriteId);
}

void Logic::setGameStateUpdater(GameStateUpdater *updater)
{
    _gameStateUpdater = updater;
    _state = updater->getState();
    AI::getInstance()->init(_state);
}

void Logic::moveSprite(Position position)
{
    if (_controlledSprite == nullptr)
    {
        std::cout << "Logic::_controlledSprite is nullptr\n";
    }

    _gameStateUpdater->moveSprite(_controlledSprite, position);
}

void Logic::moveSprite(unsigned int spriteId, Position position)
{
    _gameStateUpdater->moveSprite(_state->getSpriteLayer()->getObject(spriteId), position);
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
