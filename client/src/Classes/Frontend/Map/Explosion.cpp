#include "Explosion.h"
#include "../../Constants.h"

/*ExplosionEmitterCache *ExplosionEmitterCache::_instance = NULL;

ExplosionEmitterCache *ExplosionEmitterCache::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new ExplosionEmitterCache();
    }
    return _instance;
}*/

ExplosionEmitterCache::ExplosionEmitterCache()
: _cacheSize(EXPLOSION_CACHE_SIZE)
, _counter(-1)
{
    for (int i = 0; i < _cacheSize; i++)
    {
        ParticleSun *emitter = ParticleSun::create();
        emitter->retain();
        emitter->setTexture(TextureCache::sharedTextureCache()->addImage("particles/fire.png"));
        emitter->initWithTotalParticles(150);
        emitter->setStartSize(50.0f);
        emitter->setLife(1);
        emitter->setLifeVar(1);
        emitter->setDuration(0.5);
        emitter->setPositionType(kPositionTypeRelative);
        /*
        emitter->setSpeed(60);
        emitter->setSpeedVar(20);
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

ParticleSun *ExplosionEmitterCache::getEmitter()
{
    _counter += 1;
    _emitters[_counter % _cacheSize]->resetSystem();
    return _emitters[_counter % _cacheSize];
}

Explosion::Explosion(Point epicentrum, int powerLeft, int powerRight, int powerTop, int powerBottom) 
{
    _eec = new ExplosionEmitterCache();
    for (int i = 0; i < 4; i++)
    {
        ParticleSun *emitter = _eec->getEmitter();
        emitter->setPosition(epicentrum);
        this->addChild(emitter, -5);

        //continue;

        ActionInterval* move;

        if (i == 0)
        {
            emitter->setAngle(0);
            move = MoveBy::create(2, ccp(TILE_WIDTH*powerRight, 0));
        }
        else if (i == 1)
        {
            emitter->setAngle(90);
            move = MoveBy::create(2, ccp(0, TILE_HEIGHT*powerTop));
        }
        else if (i == 2)
        {
            emitter->setAngle(180);
            move = MoveBy::create(2, ccp(-TILE_WIDTH*powerLeft, 0));
        }
        else if (i == 3)
        {
            emitter->setAngle(-90);
            move = MoveBy::create(2, ccp(0, -TILE_HEIGHT*powerBottom));
        }
        //ActionInterval* move_back = CCHide::create();
        Sequence* seq = Sequence::create(move, NULL);
        emitter->runAction(Speed::create(seq, 5));
    }
}
