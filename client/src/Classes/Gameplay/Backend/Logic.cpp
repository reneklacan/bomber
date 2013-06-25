
#include <iostream>

#include "Logic.h"

using namespace Bomber::Backend;

Logic::Logic()
{
    _uniqueId = 1;
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
                    this->spawnExplosion(explObj);
                }
            }

        }
    }
}

void Logic::setControlledSprite(unsigned int spriteId)
{
    _controlledSprite = _state->getSpriteLayer()->getObject(spriteId);
}

bool Logic::moveSprite(Position position)
{
    if (_controlledSprite == nullptr)
    {
        std::cout << "Logic::_controlledSprite is nullptr\n";
        return false;
    }

    return this->moveSprite(_controlledSprite, position);
}

bool Logic::moveSprite(unsigned int spriteId, Position position)
{
    return this->moveSprite(_state->getSpriteLayer()->getObject(spriteId), position);
}

bool Logic::moveSprite(GameObject *sprite, Position position)
{
    this->logSpriteMove(sprite, sprite->getPosition(), position);

    sprite->setPosition(position);
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

bool Logic::spawnBomb(GameObject *owner)
{
    if (!owner->isBombPotent())
    {
        return false;
    }

    GameStateLayer *bombLayer = _state->getBombLayer();

    Bomb *bomb = new Bomb();
    bomb->configure(owner);
    bomb->setId(this->getUniqueId());

    bombLayer->addObject(bomb);

    this->logBombSpawn(bomb);

    return true;
}

void Logic::spawnExplosion(ExplodableObject *explObj)
{
    this->logExplosionSpawn(explObj);

    // spawn explosion and destroy blocks and kill sprites
}

void Logic::logSpriteMove(GameObject *sprite, Position &from, Position &to)
{
    GSCSpriteMove *change = new GSCSpriteMove();
    change->update(from, to);
    change->setGameObjectId(sprite->getId());
    _state->addChange(change);
}

void Logic::logBombSpawn(Bomb *bomb)
{
    GSCBombSpawn *change = new GSCBombSpawn();
    change->update(bomb->getPosition());
    change->setGameObjectId(bomb->getOwner());
    _state->addChange(change);
}

void Logic::logExplosionSpawn(ExplodableObject *explObj)
{
    GSCExplosionSpawn* change = new GSCExplosionSpawn();
    change->update(
            explObj->getOwner(),
            explObj->getPower(),
            explObj->getPenetration()
    );
    change->setGameObjectId(explObj->getOwner());
    _state->addChange(change);
}

