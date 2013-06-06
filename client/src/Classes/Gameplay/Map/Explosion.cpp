#include "Explosion.h"
#include "../../Constants.h"

ExplosionCache *ExplosionCache::_instance = NULL;

ExplosionCache *ExplosionCache::getInstance()
{
    if (_instance == NULL)
        _instance = new ExplosionCache();
    return _instance;
}

ExplosionCache::ExplosionCache()
{
    _cacheSize = 12;
    _counter = -1;

    for (int i = 0; i < _cacheSize; i++)
    {
       CCParticleSun *emitter = CCParticleSun::create();
        emitter->retain();
        emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("particles/fire.png"));
        emitter->initWithTotalParticles(50);
        emitter->setStartSize(100.0f);
        emitter->setLife(2);
        emitter->setLifeVar(1);
        //emitter->setSpeed(60);
        //emitter->setSpeedVar(20);
        emitter->setDuration(0.5);
        /*
        emitter->setAngleVar(0);
        emitter->setStartSpin(0);
        emitter->setStartSpinVar(0);
        emitter->setTangentialAccel(0);
        emitter->setTangentialAccelVar(0);
        emitter->setStartRadius(0);
        emitter->setStartRadiusVar(0);
        emitter->setRadialAccel(0);
        emitter->setRadialAccelVar(0);
        */
        emitter->setAutoRemoveOnFinish(false);

        _emitters[i] = emitter;
    }
}

CCParticleSun *ExplosionCache::getEmitter()
{
    _counter += 1;
    _emitters[_counter % _cacheSize]->resetSystem();
    return _emitters[_counter % _cacheSize];
}

Explosion::Explosion(CCPoint epicentrum, int power) 
{
    for (int i = 0; i < 4; i++)
    {
        CCParticleSun *emitter = ExplosionCache::getInstance()->getEmitter();
        emitter->setPosition(epicentrum);
        this->addChild(emitter, -5);

        CCActionInterval* move;

        if (i == 0)
        {
            emitter->setAngle(0);
            move = CCMoveBy::create(2, ccp(TILE_WIDTH*power, 0));
        }
        else if (i == 1)
        {
            emitter->setAngle(90);
            move = CCMoveBy::create(2, ccp(0, TILE_HEIGHT*power));
        }
        else if (i == 2)
        {
            emitter->setAngle(180);
            move = CCMoveBy::create(2, ccp(-TILE_WIDTH*power, 0));
        }
        else if (i == 3)
        {
            emitter->setAngle(-90);
            move = CCMoveBy::create(2, ccp(0, -TILE_HEIGHT*power));
        }
        //CCActionInterval* move_back = CCHide::create();
        CCSequence* seq = CCSequence::create(move, NULL);
        emitter->runAction(CCSpeed::create(seq, 5));
    }
}
