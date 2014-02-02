#ifndef __BOMBER_FRONTEND_GUICACHE_LAYER
#define __BOMBER_FRONTEND_GUICACHE_LAYER

#include "cocos2d.h"

#include "../../Input/ControlLayer.h"

#include "../Map/Map.h"
#include "../Sprites/SpriteCreator.h"
#include "../Sprites/ActionSprite.h"

#define MAX_CACHED_ITEMS  10

namespace Bomber
{
    namespace Frontend
    {
        class GUICache
        {
        public:
            static GUICache *getInstance();

            void initCaches(Map* map);
            void cacheAllLayers(Map* map);
            bool cacheObstacle(Sprite *);
            bool cacheSprite(ActionSprite * sprite);
            bool cacheEffect(Sprite * sprite);
            bool cacheBomb(Sprite * sprite);
            Sprite *getObstacle(Texture2D *texture, Rect rect);
            ActionSprite *getSprite(Texture2D *texture, Rect rect);
            Sprite *getEffect(Texture2D *texture, Rect rect);
            Sprite *getBomb(Texture2D *texture, Rect rect);
            void resetSprites();
            void setBatchNode(SpriteBatchNode* batchNode);


            std::map<unsigned int, Sprite *> *getMobs() { return &_mobs; }
            std::map<unsigned int, Sprite *> *getObstacles() { return &_obstacles; }
            std::map<unsigned int, Sprite *> *getEffects() { return &_effects; }
            std::map<unsigned int, Sprite *> *getPortals() { return &_portals; }

        private:
            GUICache() : _creator( SpriteCreator::getInstance() ) {};

            SpriteCreator *_creator;
            SpriteBatchNode* _batchNode;

            std::map<unsigned int, Sprite *> _mobs;
            std::map<unsigned int, Sprite *> _obstacles;
            std::map<unsigned int, Sprite *> _effects;
            std::map<unsigned int, Sprite *> _portals;


            std::vector<Sprite *> _bombCache;
            std::vector<Sprite *> _obstacleCache;
            std::vector<ActionSprite *> _mobCache;
            std::vector<Sprite *> _effectCache;

            unsigned int _effects2Spawn;
            unsigned int _sprites2Spawn;
        };
    }
}

#endif