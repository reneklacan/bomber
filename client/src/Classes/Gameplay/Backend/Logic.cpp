
#include <iostream>

#include "Logic.h"
#include "Bomb.h"

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
                    GSCExplosionSpawn* change = new GSCExplosionSpawn();
                    change->update(
                            explObj->getOwner(),
                            explObj->getPower(),
                            explObj->getPenetration()
                    );
                    _state->addChange(change);
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

    _controlledSprite->moveToPosition(position);
    return true;
}

bool Logic::moveSprite(unsigned int spriteId, Position position)
{
    _state->getSpriteLayer()->getObject(spriteId)->moveToPosition(position);
    return true;
}

bool Logic::spawnBomb()
{ 
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
    bomb->activate();

    bombLayer->addObject(bomb);

    return true;
}

void Logic::spawnExplosion(ExplodableObject *explObj)
{
    // spawn explosion and destroy blocks and kill sprites
}
