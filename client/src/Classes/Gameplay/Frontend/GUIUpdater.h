#ifndef __BOMBER_FRONTEND_GUIUPDATER_LAYER
#define __BOMBER_FRONTEND_GUIUPDATER_LAYER

#include "cocos2d.h"

#include <vector>

#include "../Map/Map.h"
#include "../Map/Bomb.h"
#include "../Map/Explosion.h"

#include "../Sprites/Human.h"

#include "../Backend/Mediator.h"
#include "../Backend/Bomber.h"

#include "../../Constants.h"

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

        private:
            GUIUpdater(): _lastChangeID(0) {};

            void updateSpriteMove(Backend::GSCSpriteMove *spriteMove);
            void updateSpriteTeleport(Backend::GSCSpriteTeleport *spriteTeleport, Point playerPosition);
            void updateBombSpawn(Backend::GSCBombSpawn *bombSpawn);
            void updateBombDestroy(Backend::GSCBombDestroy *bombDestroy);
            void updateObstacleDestroy(Backend::GSCObstacleDestroy *obstacleDestroy);
            void updateExplosionSpawn(Backend::GSCExplosionSpawn *explosionSpawn);

            unsigned int _lastChangeID;
            Map* _map;
            Human* _player;
            Layer * _layer;
            std::map<unsigned int, Sprite *> _mobs;
        };
    }
}

#endif