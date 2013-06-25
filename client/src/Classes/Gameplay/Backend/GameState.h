#ifndef __BOMBER_GAME_STATE
#define __BOMBER_GAME_STATE

#include "GameStateLayer.h"
#include "GameStateChange.h"

namespace Bomber
{
    namespace Backend
    {
        class GameState
        {
            public:
                GameState();
                ~GameState();

                std::vector<GameStateChange *> getChangesFromId(unsigned int id);
                void deleteChangesToId(unsigned int id);
                void addChange(GameStateChange *change);
                void gatherChanges();

                std::vector<GameStateLayer *> &getAllLayers() { return _allLayers; };
                GameStateLayer *getSpriteLayer() { return _spriteLayer; };
                GameStateLayer *getBombLayer() { return _bombLayer; };

            private:
                std::deque<GameStateChange *> _changes;
                unsigned int _lastChangeId; // id of latest change
                unsigned int _lastChangeIdOffset; // offset needed when old changes are deleted

                GameStateLayer *_spriteLayer;
                GameStateLayer *_obstacleLayer;
                GameStateLayer *_portalLayer;
                GameStateLayer *_portalExitLayer;
                GameStateLayer *_specialLayer;
                GameStateLayer *_bombLayer;

                std::vector<GameStateLayer *> _allLayers;
        };
    }
}

#endif
