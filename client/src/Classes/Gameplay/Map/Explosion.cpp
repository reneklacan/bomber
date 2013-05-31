#include "Explosion.h"
#include "../../Constants.h"

Explosion::Explosion(CCPoint epicentrum, int power) 
{
    for (int i = 0; i < 4; i++)
    {
        CCParticleFire *emitter = CCParticleFire::create();
        emitter->retain();
        this->addChild(emitter, -5);
        emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("particles/fire.png"));
        emitter->initWithTotalParticles(500);
        emitter->setStartSize(100.0f);
        emitter->setLife(2);
        emitter->setLifeVar(1);
        //emitter->setSpeed(60);
        //emitter->setSpeedVar(20);
        emitter->setDuration(0.5);
        emitter->setPosition(epicentrum);
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
        emitter->setAngleVar(0);
        emitter->setAutoRemoveOnFinish(true);
        //CCActionInterval* move_back = CCHide::create();
        CCSequence* seq = CCSequence::create(move, NULL);
        emitter->runAction(CCSpeed::create(seq, 5));
    }
}
