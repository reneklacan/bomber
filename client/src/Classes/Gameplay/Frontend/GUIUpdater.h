#ifndef __BOMBER_FRONTEND_GUIUPDATER_LAYER
#define __BOMBER_FRONTEND_GUIUPDATER_LAYER

#include "cocos2d.h"

#include <vector>

#include "Map/Map.h"
#include "Map/Bomb.h"
#include "Map/Explosion.h"

#include "Sprites/Human.h"

#include "../Backend/Mediator.h"
#include "../Backend/Bomber.h"
#include "../Backend/Effect.h"

#include "../../Constants.h"
#include "GUIConstants.h"

#include "Buttons/AchievementButton.h"
#include "Buttons/EffectButton.h"
#include "ButtonLayer.h"

namespace Bomber
{
    namespace Frontend
    {
        class GUIUpdater
        {
        public:
            static GUIUpdater *getInstance();

            void init( Map* map, Human* player, Layer* layer);
            void update(Point playerPosition);
            std::vector<bool> evalCollisions(Point currentPoint, Point nextPoint);
            void resetGUI();

        private:
            GUIUpdater(): _lastChangeID(0), _batchNode(NULL) {};

            void updateSpriteMove(Backend::GSCSpriteMove *spriteMove);
            void updateSpriteTeleport(Backend::GSCSpriteTeleport *spriteTeleport, Point playerPosition);
            void updateBombSpawn(Backend::GSCBombSpawn *bombSpawn);
            void updateBombDestroy(Backend::GSCBombDestroy *bombDestroy);
            void updateObstacleDestroy(Backend::GSCObstacleDestroy *obstacleDestroy);
            void updateExplosionSpawn(Backend::GSCExplosionSpawn *explosionSpawn);
            void updateAchievementUnlocked(Backend::GSCAchievementUnlocked *achievementUnlocked);
            void updateObstacleSpawn(Backend::GSCObstacleSpawn *obstacleSpawn);
            void updateSpriteDestroy( Backend::GSCSpriteDestroy *spriteDestroy );
            void updateLeverSwitchOn( Backend::GSCLeverSwitchOn *leverSwitchOn );
            void updateLeverSwitchOff( Backend::GSCLeverSwitchOff *leverSwitchOff );
            void updateSpriteDamage( Backend::GSCSpriteDamage *spriteDamage );
            void updateSpriteAttrUpdate( Backend::GSCSpriteAttrUpdate *spriteAttrUpdate );
            void updateEffectDestroy( Backend::GSCEffectDestroy *effectDestroy );
            void updateSpriteSpawn( Backend::GSCSpriteSpawn *spriteSpawn );
            void updateEffectSpawn( Backend::GSCEffectSpawn *effectSpawn );

            void initLayers();
            void initPlayer();
            Rect pickImageFromTexture(unsigned int id);
            bool evalCollision(Point nextPoint);

            unsigned int _lastChangeID;
            Map* _map;
            Human* _player;
            Layer * _layer;

            std::map<unsigned int, Sprite *> _mobs;
            std::map<unsigned int, Node *> _obstacles;
            std::map<unsigned int, Node *> _effects;

            SpriteBatchNode* _batchNode;
            TMXLayer *_obstaclesLayer;
        };
    }
}

#endif