
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

        this->makeBombImpact(bomb, NULL, epicentrum);

        for (int i = 0; i < power; i++)
        {
            auto around = epicentrum.getCoordsAround(i + 1);

            for (int j = 0; j < 4; j++)
            {
                int *penetration = penetrations[j];

                if (*penetration == 0)
                    continue;

                auto coords = around[j];

                for (auto bombObject : _state->getBombLayer()->getObjectsAtCoords(coords))
                {
                    if (!bombObject->isDetonated())
                    {
                        bombsToDetonate.push_back(bombObject);
                        bombObject->detonate();
                    }
                    *penetration = 0;
                }

                if (*penetration == 0)
                {
                    armLengths[j]++;
                    continue;
                }

                if (this->makeBombImpact(bomb, penetrations[j], coords))
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
        
        auto effects = effectLayer->getObjectsAtCoords(sprite->getCoords());

        for (auto object : effects)
        {
            Effect *effect = (Effect *) object;

            _gameStateUpdater->updateSpriteAttributes(sprite, effect);
            effectsToDestroy.push_back(effect);
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

    for (auto effect : effectsToDestroy)
    {
        _gameStateUpdater->destroyEffect(effect);
    }

    _gameStateUpdater->updateSpriteGrid();
    _gameStateUpdater->updateAchievements();

    //_state->getSpriteLayer()->print();
}


bool Logic::makeBombImpact(BBomb *bomb, int *penetration, Coordinates coords)
{
    unsigned int x = coords.x;
    unsigned int y = coords.y;

    if (penetration != NULL && !(*penetration))
        return false;

    auto levers = _state->getLeverLayer()->getObjectsAtCoords(x, y);

    for (auto lever : levers)
    {
        auto target = _state->getLeverTargetLayer()->getObject(lever->getId());
        auto obstacles = _state->getObstacleLayer()->getObjectsAtCoords(target->getCoords());


        if (obstacles.size() > 0)
        {
            // open "the bridge"
            _gameStateUpdater->switchLeverOn(lever);

            for (auto obstacle : obstacles)
            {
                _gameStateUpdater->destroyObstacle(obstacle, bomb->getId());
            }
        }
        else
        {
            // close "the bridge"
            _gameStateUpdater->switchLeverOff(lever);

            unsigned int obstacleGid = 20;
            _gameStateUpdater->spawnObstacle(obstacleGid, target->getCoords(), bomb->getId());
        }
    }

    auto sprites = _state->getSpriteLayer()->getObjectsAtCoords(x, y);

    for (auto sprite : sprites)
    {
        if (!sprite->isAI()) continue; // temporary

        _gameStateUpdater->damageSprite(sprite, bomb->getId(), bomb->getDamage());
    }

    if (penetration == NULL)
        return true;

    auto obstacles = _state->getObstacleLayer()->getObjectsAtCoords(x, y);

    if (obstacles.size() == 0)
        return true;

    bool somethingDamaged = false;

    for (auto object : obstacles)
    {
        Obstacle *obstacle = (Obstacle *) object;

        if (obstacle->getToughness() == -1)
        {
            *penetration = 0;
            return false;
        }
        
        _gameStateUpdater->damageObstacle(obstacle, bomb->getOwnerId());

        if (obstacle->getToughness() == 0)
        {
            _gameStateUpdater->spawnEffect(18, obstacle->getCoords()); // temporary
        }

        somethingDamaged = true;
    }

    if (somethingDamaged)
    {
        (*penetration)--;
    }

    return somethingDamaged;
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
