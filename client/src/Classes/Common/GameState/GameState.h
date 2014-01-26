#ifndef __BOMBER_GAME_STATE
#define __BOMBER_GAME_STATE

#include "cocos2d.h"

#include "GameStateLayer.h"
#include "GameStateChange.h"
#include "../../Backend/GameObjects/Sprites/Sprite.h"
#include "../../Backend/GameObjects/BBomb.h"
#include "../../Backend/GameObjects/Obstacle.h"
#include "../../Backend/GameObjects/Portal.h"
#include "../../Backend/GameObjects/PortalExit.h"
#include "../../Backend/GameObjects/Effect.h"
#include "../../Backend/GameObjects/Switch.h"

namespace Bomber
{
    namespace Common
    {
        enum TGoalConditionsTypes
        {
            CONDITION_MOBS_ALIVE,
            CONDITION_LEVEL_KEYS,
        };

        typedef std::map<TGoalConditionsTypes, int> TGoalConditions;
        typedef std::pair<int, int> TSpawnPoint;

        class GameState
        {
            public:
                GameState(unsigned int width, unsigned int height);
                ~GameState();

                void init(cocos2d::TMXTiledMap *tiledMap);
                void reset();

                std::pair< unsigned int, std::vector<GameStateChange *> > getChangesFromId(unsigned int id);
                void deleteChangesToId(unsigned int id);
                void addChange(GameStateChange *change);
                void gatherChanges();
                void setSpawnPoint(unsigned int id);

            private:
                std::deque<GameStateChange *> _changes;
                unsigned int _lastChangeId; // id of latest change
                unsigned int _lastChangeIdOffset; // offset needed when old changes are deleted

                SYNTHESIZE(bool, _goalReached, GoalReached);
                SYNTHESIZE(TGoalConditions, _goalConditions, GoalConditions);

                SYNTHESIZE(TSpawnPoint, _spawnPoint, SpawnPoint);

                SYNTHESIZE_READONLY(unsigned int, _width, Width);
                SYNTHESIZE_READONLY(unsigned int, _height, Height);

                SYNTHESIZE_READONLY(cocos2d::TMXTiledMap *, _tiledMap, TiledMap);

                SYNTHESIZE_READONLY(GameStateLayer<Backend::Sprite> *, _spriteLayer, SpriteLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Backend::Obstacle> *, _obstacleLayer, ObstacleLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Backend::Bomb> *, _bombLayer, BombLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Backend::Portal> *, _portalLayer, PortalLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Backend::PortalExit> *, _portalExitLayer, PortalExitLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Backend::Effect> *, _effectLayer, EffectLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Backend::GameObject> *, _specialLayer, SpecialLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Backend::Switch> *, _switchLayer, SwitchLayer);
                SYNTHESIZE_READONLY(GameStateLayer<Backend::GameObject> *, _switchTargetLayer, SwitchTargetLayer);
        };
    }
}

#endif
