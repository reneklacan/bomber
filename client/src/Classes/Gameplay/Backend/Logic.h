#ifndef __BOMBER_LOGICv2
#define __BOMBER_LOGICv2

#include "State/GameState.h"
#include "State/GameStateUpdater.h"
#include "GameObjects/BBomb.h"
#include "Interactions/Movement.h"

namespace Bomber
{
    namespace Backend
    {
        class Logic
        {
            public:
                static Logic* getInstance();

                void update(float dt);
                void updateBombs(float dt);
                void updateMovements(float dt);
                void updateSprites(float dt);

                void setState(GameState *state) { _state = state; };
                inline GameState *getState() { return _state; };

                void scheduleLevelReset(float delay);

                void moveSprite(Common::Position position);
                void moveSprite(unsigned int id, Common::Position position);
                void moveSprite(GameObject *sprite, Common::Position position);

                bool spawnBomb();
                bool spawnBomb(unsigned int);
                bool spawnBomb(Sprite *owner);

                void spawnExplosion(ExplodableObject *explObj);

                bool makeBombImpact(Bomb *bomb, Common::Coordinates coords, int *penetration, int *spritesKilled);

                void kickBomb(Common::Coordinates coords, int direction);
                void pushBlock(Common::Coordinates coords, int direction);
                
                void setControlledSprite(unsigned int id);
                void setGameStateUpdater(GameStateUpdater *updater);

            private:
                Logic();

                static Logic *_instance;
                GameState *_state;
                GameStateUpdater *_gameStateUpdater;
                Sprite *_controlledSprite;
                bool _restartScheduled;
                float _timeToRestart;
                std::set<Movement *> _movements;
        };
    }
}

#endif
