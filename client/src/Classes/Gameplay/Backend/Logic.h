#ifndef __BOMBER_LOGICv2
#define __BOMBER_LOGICv2

#include "GameState.h"
#include "Bomb.h"

namespace Bomber
{
    namespace Backend
    {
        class Logic
        {
            public:
                static Logic* getInstance();

                Logic();

                void update(float dt);
                void setState(GameState *state) { _state = state; };

                bool moveSprite(Position position);
                bool moveSprite(unsigned int id, Position position);
                bool moveSprite(GameObject *sprite, Position position);

                bool spawnBomb();
                bool spawnBomb(unsigned int);
                bool spawnBomb(GameObject *owner);

                void spawnExplosion(ExplodableObject *explObj);

                void logSpriteMove(GameObject *sprite, Position &from, Position &to);
                void logBombSpawn(Bomb *bomb);
                void logExplosionSpawn(ExplodableObject *explObj);
                
                unsigned int getUniqueId() { return _uniqueId++; };
                void setControlledSprite(unsigned int id);

            private:
                static Logic *_instance;
                GameState *_state;
                GameObject *_controlledSprite;
                unsigned int _uniqueId;
        };
    }
}

#endif
