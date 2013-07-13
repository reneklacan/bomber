#ifndef __BOMBER_FRONTEND_GUICACHE_LAYER
#define __BOMBER_FRONTEND_GUICACHE_LAYER

#include "cocos2d.h"

#include "../../../Input/ControlLayer.h"

#include "../Map/Map.h"

namespace Bomber
{
    namespace Frontend
    {
        class GUICache
        {
        public:
            static GUICache *getInstance();

            void cacheAllLayers(Map* map);
            void cacheObstacle();
            void cacheSprite();

            std::map<unsigned int, Sprite *> *getMobs() { return &_mobs; }
            std::map<unsigned int, Sprite *> *getObstacles() { return &_obstacles; }
            std::map<unsigned int, Sprite *> *getEffects() { return &_effects; }

        private:
            GUICache() {};

            std::map<unsigned int, Sprite *> _mobs;
            std::map<unsigned int, Sprite *> _obstacles;
            std::map<unsigned int, Sprite *> _effects;
        };
    }
}

#endif