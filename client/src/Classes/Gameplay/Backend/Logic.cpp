
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
        
    unsigned int ownerId;
    Sprite *owner;

    Coordinates epicentrum;
    
    std::vector<BBomb *> bombsToDestroy;
    std::deque<BBomb *> bombsToDetonate;
    BBomb *bomb;

    for (auto bomb : _state->getBombLayer()->getObjects())
    {
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
        ownerId = bomb->getOwnerId();

        owner = _state->getSpriteLayer()->getObject(ownerId);
        owner->getAttributes()->increaseBombCapacity();
            
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

    for (auto sprite : spriteLayer->getObjects())
    {
        if (!sprite->isActive())
            continue;

        sprite->update(dt);

        if (sprite->isAI() && sprite->isDirty())
        {
            _gameStateUpdater->logSpriteMove(sprite);
        }
        
        auto effects = effectLayer->getObjectsAtCoords(sprite->getCoords());

        for (Effect *effect : effects)
        {
            if (!effect->isActive())
                continue;

            if (effect->getCharges() == 0)
                continue;

            _gameStateUpdater->updateSpriteAttributes(sprite, effect);
            effectsToDestroy.push_back(effect);
        }

        if (sprite->getAttributes()->getPortability() == false)
        {
            continue;
        }

        auto portals = portalLayer->getObjectsAtCoords(sprite->getCoords());

        for (Portal *portal : portals)
        {
            auto portalExit = portalExitLayer->getObject(portal->getPortalTarget(sprite->getPreviousCoords()));
            _gameStateUpdater->teleportSprite(sprite, portalExit->getPosition());
        }
    }

    for (auto effect : effectsToDestroy)
    {
        _gameStateUpdater->destroyEffect(effect);
    }

    _gameStateUpdater->updateSpriteGrid();
    _gameStateUpdater->update();

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
        auto targets = _state->getLeverTargetLayer()->getObjects(lever->getId());

        for (auto target : targets)
        {
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
    }

    auto sprites = _state->getSpriteLayer()->getObjectsAtCoords(x, y);

    for (auto sprite : sprites)
    {
        if (!sprite->isActive())
            continue;

        if (sprite->getAttributes()->isDead())
            continue;

        //if (!sprite->isAI()) continue; // temporary

        _gameStateUpdater->damageSprite(sprite, bomb->getOwnerId(), bomb->getDamage());

        if (sprite == _controlledSprite && sprite->getAttributes()->isDead())
        {
            _gameStateUpdater->resetLevel();
        }
    }

    if (penetration == NULL)
        return true;

    auto obstacles = _state->getObstacleLayer()->getObjectsAtCoords(x, y);

    if (obstacles.size() == 0)
        return true;

    bool somethingDamaged = false;

    for (auto obstacle : obstacles)
    {
        if (obstacle->getToughness() == -1)
        {
            *penetration = 0;
            return false;
        }
        
        _gameStateUpdater->damageObstacle(obstacle, bomb->getOwnerId());

        if (obstacle->getToughness() == 0)
        {
            auto effectsToSpawn = _state->getEffectLayer()->getObjectsAtCoords(obstacle->getCoords());

            for (Effect *effect : effectsToSpawn)
            {
                if (effect->isActive())
                    continue;

                effect->setActive(true);
                _gameStateUpdater->logEffectSpawn(effect);
            }
                        
            auto spritesToSpawn = _state->getSpriteLayer()->getObjectsAtCoords(obstacle->getCoords());

            for (Sprite *sprite : spritesToSpawn)
            {
                if (sprite->isActive())
                    continue;

                sprite->setActive(true);
                _gameStateUpdater->logSpriteSpawn(sprite);
            }
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
    _controlledSprite = _state->getSpriteLayer()->getObject(spriteId);
    _controlledSprite->getAttributes()->reset();
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

    return this->spawnBomb(_controlledSprite);
}

bool Logic::spawnBomb(unsigned int spriteId)
{
    return this->spawnBomb(_state->getSpriteLayer()->getObject(spriteId));
}

bool Logic::spawnBomb(Sprite *owner)
{
    if (owner->getAttributes()->getBombCapacity() <= 0)
    {
        return false;
    }

    if (_state->getObstacleLayer()->getObjectsAtCoords(owner->getCoords()).size() != 0)
    {
        printf("bomb spawn failed, tile occupied by obstacle\n");
        return false;
    }

    if (_state->getBombLayer()->getObjectsAtCoords(owner->getCoords()).size() != 0)
    {
        printf("bomb spawn failed, tile occupied by another bomb\n");
        return false;
    }
    
    owner->getAttributes()->decreaseBombCapacity();

    _gameStateUpdater->spawnBomb(owner);

    return true;
}
