#ifndef __BOMBER_FRONTEND_GUIUPDATER_LAYER
#define __BOMBER_FRONTEND_GUIUPDATER_LAYER

#include "cocos2d.h"

#include <vector>

#include "Map/Map.h"
#include "Map/Explosion.h"

#include "Sprites/Human.h"
#include "Sprites/ActionSprite.h"

#include "../Backend/Mediator.h"
#include "../Backend/GameObjects/Sprites/Bomber.h"
#include "../Backend/GameObjects/Effect.h"
#include "../Common/Primitives/Direction.h"

#include "../Constants.h"
#include "GUIConstants.h"
#include "Collisions.h"

#include "Buttons/AchievementButton.h"
#include "Buttons/EffectButton.h"
#include "Buttons/Bubble.h"
#include "Layers/ButtonLayer.h"

#include "Cache/GUICache.h"

#include "Primitives/AnimationHelper.h"
#include "Primitives/CollisionArea.h"
#include "Primitives/Shapes.h"

#include "Statistics/FStatistics.h"

namespace Bomber
{
    namespace Frontend
    {
        class GUIUpdater
        {
        public:
            GUIUpdater(): _lastChangeID(0), _batchNode(NULL) {};

            void init(Map* map, SpriteBatchNode* node, std::map<unsigned int, Human *> &players, Layer* layer, Statistics* stats);
            void update();
            std::vector<bool> evalCollisions(Human *sprite);
            void resetGUI(std::map<unsigned int, Human *> &players);
            bool isResetSet() {return _resetNow; }
            bool isFinishSet() {return _finishLevel; }
            bool obstacleExists(unsigned int id);
            bool isPlayerAlive(unsigned int id);

        private:

            void updateSpriteMove(Common::GSCSpriteMove *spriteMove);
            void updateSpriteTeleport(Common::GSCSpriteTeleport *spriteTeleport);
            void updateBombSpawn(Common::GSCBombSpawn *bombSpawn);
            void updateBombDestroy(Common::GSCBombDestroy *bombDestroy);
            void updateObstacleDestroy(Common::GSCObstacleDestroy *obstacleDestroy);
            void updateExplosionSpawn(Common::GSCExplosionSpawn *explosionSpawn);
            void updateAchievementUnlocked(Common::GSCAchievementUnlocked *achievementUnlocked);
            void updateObstacleSpawn(Common::GSCObstacleSpawn *obstacleSpawn);
            void updateSpriteDestroy( Common::GSCSpriteDestroy *spriteDestroy );
            void updateLeverSwitchOn( Common::GSCLeverSwitchOn *leverSwitchOn );
            void updateLeverSwitchOff( Common::GSCLeverSwitchOff *leverSwitchOff );
            void updateSpriteDamage( Common::GSCSpriteDamage *spriteDamage );
            void updateSpriteAttrUpdate( Common::GSCSpriteAttrUpdate *spriteAttrUpdate );
            void updateEffectDestroy( Common::GSCEffectDestroy *effectDestroy );
            void updateSpriteSpawn( Common::GSCSpriteSpawn *spriteSpawn );
            void updateEffectSpawn( Common::GSCEffectSpawn *effectSpawn );
            void updateLevelReset( Common::GSCLevelReset *levelReset );
            void updateLevelFinish( Common::GSCLevelFinish *levelFinish );
            void updateBombMove( Common::GSCBombMove *bombMove );
            void updateBlockPush( Common::GSCBlockPush *blockPush );
            void updateDialogBubble( Common::GSCDialogBubble *GSChange );
            void updateFogOn( Common::GSCFogOn *GSChange );
            void updateFogOff( Common::GSCFogOff *GSChange );
            void finishUpdateBlockPush(ObstacleMove* move);

            void initLayers();
            void initPlayers();
            Sprite *getBombAtPosition(int x, int y);

            unsigned int _lastChangeID;
            Map* _map;
            std::vector<Human *> _players;
            Layer * _layer;

            std::map<unsigned int, ActionSprite *> _mobs;
            std::map<unsigned int, Sprite *> _obstacles;
            std::map<unsigned int, Sprite *> _effects;
            std::map<unsigned int, Sprite *> _bombs;
            std::map<unsigned int, Sprite *> _portals;

            SpriteBatchNode* _batchNode;
            bool _resetNow;
            bool _finishLevel;
            GUICache *_cache;
            Backend::Mediator *_mediator;
            Collisions *_collisionDetector;
            Statistics *_statistics;

            // Opt
            unsigned int _O_mapPixelHeight;
            unsigned int _O_tileHeightDiv4;
        };
    }
}

#endif