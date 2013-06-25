
#ifndef __BOMBER_LOGICv2
#define __BOMBER_LOGICv2

#include "GameState.h"

namespace Bomber
{
    namespace Backend
    {
        class Logic
        {
            public:
                Logic();

                void update(float dt);
                void setState(GameState *state) { _state = state; };
                bool moveSprite(Position position);
                bool moveSprite(unsigned int id, Position position);
                bool spawnBomb();
                bool spawnBomb(unsigned int);
                bool spawnBomb(GameObject *owner);
                void spawnExplosion(ExplodableObject *explObj);
                
                unsigned int getUniqueId() { return _uniqueId++; };
                void setControlledSprite(unsigned int id);

            private:
                GameState *_state;
                GameObject *_controlledSprite;
                unsigned int _uniqueId;
        };
    }
}

#endif
