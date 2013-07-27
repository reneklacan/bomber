#ifndef __BOMBER_FRONTEND_GUIUPDATER_LAYER
#define __BOMBER_FRONTEND_GUIUPDATER_LAYER

#include "cocos2d.h"

#include <vector>

#include "Map/Map.h"
#include "Map/Explosion.h"

#include "Sprites/Human.h"

#include "../Backend/Mediator.h"
#include "../Backend/GameObjects/Sprites/Bomber.h"
#include "../Backend/GameObjects/Effect.h"
#include "../Common/Primitives/Direction.h"

#include "../../Constants.h"
#include "GUIConstants.h"
#include "Collisions.h"

#include "Buttons/AchievementButton.h"
#include "Buttons/EffectButton.h"
#include "ButtonLayer.h"

#include "Cache/GUICache.h"

#include "Primitives/AnimationHelper.h"

namespace Bomber
{
    namespace Frontend
    {
        class GUIUpdater
        {
        public:
            static GUIUpdater *getInstance();

            void init(Map* map, Human* player1, Human* player2, Layer* layer);
            void update();
            std::vector<bool> evalCollisions(Point currentPoint, Point nextPoint);
            void resetGUI();
            bool isResetSet() {return _resetNow; }
            bool obstacleExists(unsigned int id);

        private:
            GUIUpdater(): _lastChangeID(0), _batchNode(NULL) {};

            void updateSpriteMove(Common::GSCSpriteMove *spriteMove);
            void updateSpriteTeleport(Common::GSCSpriteTeleport *spriteTeleport, Point playerPosition);
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
            void finishUpdateBlockPush(ObstacleMove* move);

            void initLayers();
            void initPlayer();
            Rect pickImageFromTexture(unsigned int id);
            Sprite *getBombAtPosition(int x, int y);

            unsigned int _lastChangeID;
            Map* _map;
            Human* _player1;
            Human* _player2;
            Layer * _layer;
            bool _player1Destroyed;
            bool _player2Destroyed;

            std::map<unsigned int, Sprite *> _mobs;
            std::map<unsigned int, Sprite *> _obstacles;
            std::map<unsigned int, Sprite *> _effects;
            std::map<unsigned int, Sprite *> _bombs;
            std::map<unsigned int, Sprite *> _portals;

            SpriteBatchNode* _batchNode;
            bool _resetNow;
            GUICache *_cache;
            Backend::Mediator *_mediator;
            Collisions *_collisionDetector;

            // Opt
            unsigned int _O_mapPixelHeight;
            unsigned int _O_tileHeightDiv4;
        };
    }
}

#endif