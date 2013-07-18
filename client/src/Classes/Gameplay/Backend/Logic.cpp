
#include <iostream>

#include "Logic.h"
#include "GameObjects/Obstacle.h"
#include "GameObjects/Portal.h"
#include "GameObjects/Effect.h"
#include "AI/AI.h"
#include "Statistics/StatisticsUpdater.h"

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
:_controlledSprite(nullptr)
,_restartScheduled(false)
,_timeToRestart(0.0f)
{

}

void Logic::update(float dt)
{
    this->updateMovements(dt);
    this->updateBombs(dt);
    this->updateSprites(dt);

    _gameStateUpdater->updateSpriteGrid();
    _state->getBombLayer()->updateGrid();
    _gameStateUpdater->update();

    if (_restartScheduled)
    {
        _timeToRestart -= dt;

        if (_timeToRestart <= 0.0f)
        {
            _restartScheduled = false;
            _gameStateUpdater->resetLevel();
        }
    }
}

void Logic::updateBombs(float dt)
{    
    int power,
        penetration, penetrationTop, penetrationBottom,
        penetrationRight, penetrationLeft,
        spritesKilled = 0;
        
    unsigned int ownerId;
    Sprite *owner;

    Coordinates epicentrum;
    
    std::vector<Bomb *> bombsToDestroy;
    std::deque<Bomb *> bombsToDetonate;
    Bomb *bomb;
    /*
    // TODO: bomb teleporting
    auto portalLayer = _state->getPortalLayer();
    auto portalExitLayer = _state->getPortalExitLayer();
    */

    for (auto bomb : _state->getBombLayer()->getObjects())
    {
        bomb->update(dt);

        /*
        // TODO: bomb teleporting
        auto portals = portalLayer->getObjectsAtCoords(bomb->getCoords());

        for (Portal *portal : portals)
        {
            auto portalExit = portalExitLayer->getObject(portal->getPortalTarget(bomb->getPreviousCoords()));
            bomb->setPosition(portalExit->getPosition());
            break;
        }
        */

        if (bomb->isDetonated())
        {
            bombsToDetonate.push_back(bomb);
        }
        else if (bomb->isDirty())
        {
            _gameStateUpdater->logBombMove(bomb);
        }
    }

    while (bombsToDetonate.size() > 0)
    {
        bomb = bombsToDetonate.front();
        bombsToDetonate.pop_front();
        bomb->detonate();
        bomb->setActive(false);

        power = bomb->getPower();
        epicentrum = bomb->getCoords();
        penetration = bomb->getPenetration();
        ownerId = bomb->getOwnerId();

        owner = _state->getSpriteLayer()->getObject(ownerId);

        if (owner != nullptr)
        {
            owner->getAttributes()->increaseBombCapacity();
        }
            
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

        this->makeBombImpact(bomb, epicentrum, NULL, &spritesKilled);

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

                if (this->makeBombImpact(bomb, coords, penetrations[j], &spritesKilled))
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
    }

    for (auto bomb : bombsToDestroy)
    {
        _gameStateUpdater->destroyBomb(bomb);
    }

    if (spritesKilled > 0)
    {
        StatisticsUpdater::getInstance()->updateKillStreaks(spritesKilled);
    }
}

void Logic::updateMovements(float dt)
{
    std::set<Movement *> movementsToDestroy;

    for (auto movement : _movements)
    {
        movement->update(dt);

        if (!movement->getObject()->isActive() || movement->isFinished())
        {
            movementsToDestroy.insert(movement);
        }
    }

    for (auto movement : movementsToDestroy)
    {
        _movements.erase(movement);
    }
}

void Logic::updateSprites(float dt)
{
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
            break;
        }
    }

    for (auto effect : effectsToDestroy)
    {
        _gameStateUpdater->destroyEffect(effect);
    }
}

void Logic::scheduleLevelReset(float delay)
{
    _restartScheduled = true;
    _timeToRestart = delay;
}

bool Logic::makeBombImpact(Bomb *bomb, Coordinates coords, int *penetration, int *spritesKilled)
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
                _gameStateUpdater->switchLeverOn(lever, bomb->getOwnerId());

                for (auto obstacle : obstacles)
                {
                    _gameStateUpdater->destroyObstacle(obstacle, bomb->getId());
                }
            }
            else
            {
                // close "the bridge"
                _gameStateUpdater->switchLeverOff(lever, bomb->getOwnerId());

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

        
        if (sprite->getAttributes()->isDead())
        {
            *spritesKilled = *spritesKilled + 1;
        }

        if (sprite == _controlledSprite && sprite->getAttributes()->isDead())
        {
            this->scheduleLevelReset(2.0f);
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
    StatisticsUpdater::getInstance()->setRelevantSpriteId(spriteId);
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

void Logic::kickBomb(Coordinates coords, int direction)
{
    if (!_controlledSprite->getAttributes()->getBombKicking())
        return;

    if(_state->getBombLayer()->getObjectsAtCoords(coords).size() == 0)
        return;

    Coordinates goalCoords = coords;
    Coordinates nextCoords = coords;

    while (true)
    {
        nextCoords = nextCoords.getNext(direction);
        
        if (_state->getObstacleLayer()->getObjectsAtCoords(nextCoords).size() > 0)
            break;

        if (_state->getBombLayer()->getObjectsAtCoords(nextCoords).size() > 0)
            break;

        goalCoords = nextCoords;
    }

    if (goalCoords == coords)
        return;

    Bomb *bomb = _state->getBombLayer()->getObjectsAtCoords(coords)[0];

    if (bomb->isInMovement())
        return;

    Movement *movement = new Movement(bomb, goalCoords, direction, 200);
    _movements.insert(movement);
}

void Logic::pushBlock(Coordinates coords, int direction)
{
    if (!_controlledSprite->getAttributes()->getBlockPushing())
        return;

    auto blocks = _state->getObstacleLayer()->getObjectsAtCoords(coords);
    if (blocks.size() > 1 || blocks.size() == 0)
        return;

    auto block = blocks[0];
    if (!block->isPushable())
        return;

    Coordinates nextCoords = coords.getNext(direction);

    if (_state->getObstacleLayer()->getObjectsAtCoords(nextCoords).size() > 0)
        return;

    if (_state->getSpriteLayer()->getObjectsAtCoords(nextCoords).size() > 0)
        return;
    
    _gameStateUpdater->pushBlock(coords, nextCoords);
    _gameStateUpdater->destroyObstacle(block, 0); // comment this line out when push block change is implemented
    _gameStateUpdater->spawnObstacle(block->getGid(), nextCoords, 0); // comment this line out when push block change is implemented
}
