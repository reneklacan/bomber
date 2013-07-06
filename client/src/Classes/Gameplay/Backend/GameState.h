#ifndef __BOMBER_GAME_STATE
#define __BOMBER_GAME_STATE

#include "cocos2d.h"

#include "GameStateLayer.h"
#include "GameStateChange.h"
#include "Sprite.h"
#include "BBomb.h"
#include "Obstacle.h"
#include "Portal.h"
#include "PortalExit.h"
#include "Effect.h"

namespace Bomber
{
    namespace Backend
    {
        class GameState
        {
            public:
                GameState(unsigned int width, unsigned int height);
                ~GameState();

                void init(cocos2d::TMXTiledMap *tiledMap);

                std::pair< unsigned int, std::vector<GameStateChange *> > getChangesFromId(unsigned int id);
                void deleteChangesToId(unsigned int id);
                void addChange(GameStateChange *change);
                void gatherChanges();

            private:
                std::deque<GameStateChange *> _changes;
                unsigned int _lastChangeId; // id of latest change
                unsigned int _lastChangeIdOffset; // offset needed when old changes are deleted

                SYNTHESIZE_READONLY(unsigned int, _width, Width);
                SYNTHESIZE_READONLY(unsigned int, _height, Height);
                SYNTHESIZE_READONLY(GameStateLayer<Sprite> *, _spriteLayer, SpriteLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Obstacle> *, _obstacleLayer, ObstacleLayer);
                SYNTHESIZE_READONLY(GameStateLayer<BBomb> *, _bombLayer, BombLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Portal> *, _portalLayer, PortalLayer);
                SYNTHESIZE_READONLY(GameStateLayer<PortalExit> *, _portalExitLayer, PortalExitLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Effect> *, _effectLayer, EffectLayer);
                SYNTHESIZE_READONLY(GameStateLayer<GameObject> *, _specialLayer, SpecialLayer);
        };
    }
}

#endif
