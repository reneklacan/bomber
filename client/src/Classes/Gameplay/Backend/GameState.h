#ifndef __BOMBER_GAME_STATE
#define __BOMBER_GAME_STATE

#include "cocos2d.h"

#include "GameStateLayer.h"
#include "GameStateChange.h"

using namespace cocos2d;

namespace Bomber
{
    namespace Backend
    {
        class GameState
        {
            public:
                GameState(unsigned int width, unsigned int height);
                ~GameState();

                void init(CCTMXTiledMap *tiledMap);

                std::pair< unsigned int, std::vector<GameStateChange *> > getChangesFromId(unsigned int id);
                void deleteChangesToId(unsigned int id);
                void addChange(GameStateChange *change);
                void gatherChanges();

                unsigned int getWidth() { return _width; };
                unsigned int getHeight() { return _height; };
                std::vector<GameStateLayer *> &getAllLayers() { return _allLayers; };
                GameStateLayer *getSpriteLayer() { return _spriteLayer; };
                GameStateLayer *getObstaclesLayer() { return _obstacleLayer; };
                GameStateLayer *getBombLayer() { return _bombLayer; };
                GameStateLayer *getPortalLayer() { return _portalLayer; };
                GameStateLayer *getPortalExitLayer() { return _portalExitLayer; };
                GameStateLayer *getEffectLayer() { return _effectLayer; };
                GameStateLayer *getSpecialLayer() { return _specialLayer; };

            private:
                unsigned int _width;
                unsigned int _height;

                std::deque<GameStateChange *> _changes;
                unsigned int _lastChangeId; // id of latest change
                unsigned int _lastChangeIdOffset; // offset needed when old changes are deleted

                GameStateLayer *_spriteLayer;
                GameStateLayer *_obstacleLayer;
                GameStateLayer *_bombLayer;
                GameStateLayer *_portalLayer;
                GameStateLayer *_portalExitLayer;
                GameStateLayer *_effectLayer;
                GameStateLayer *_specialLayer;

                std::vector<GameStateLayer *> _allLayers;
        };
    }
}

#endif
