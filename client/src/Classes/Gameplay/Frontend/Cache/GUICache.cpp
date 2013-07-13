#include "GUICache.h"

using namespace Bomber::Frontend;

//
GUICache *GUICache::getInstance()
{
    static GUICache instance;
    return &instance;
}

//
void GUICache::cacheAllLayers(Map* map)
{
    // Clear
    _mobs.clear();
    _obstacles.clear();
    _effects.clear();

    // Sprites
    TMXLayer *spritesLayer = map->getTiledMap()->layerNamed("sprites");

    // Obstacles
    TMXLayer *obstaclesLayer = map->getTiledMap()->layerNamed("obstacles");

    // Effects
    TMXLayer *effectsLayer = map->getTiledMap()->layerNamed("effects");

    // Init obstacles, mobs and effects structure
    for(int ix = 0; ix < map->getWidth(); ix++)
    {
        for(int iy = 0; iy < map->getHeight(); iy++)
        {
            Point point = ccp(ix, iy);
            if(obstaclesLayer->tileGIDAt( point ) != 0)
            {
                int position = map->getWidth() * iy + ix;
                _obstacles[ position ] = obstaclesLayer->tileAt( point );
            }

            if(spritesLayer->tileGIDAt( point ) != 0)
            {
                int position = map->getWidth() * (map->getHeight() - iy - 1) + ix;
                _mobs[ position ] = spritesLayer->tileAt( point );
            }

            if(effectsLayer->tileGIDAt( point ) != 0)
            {
                int position = map->getWidth() * iy + ix;
                _effects[ position ] = effectsLayer->tileAt( point );
            }

        }
    }
}

//
void GUICache::cacheObstacle()
{
    return;
}

//
void GUICache::cacheSprite()
{
    return;
}