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
void GUICache::cacheObstacle(Sprite * sprite)
{
    if( _obstacleCache.size() < MAX_CACHED_ITEMS )
    {
        _obstacleCache.push_back(sprite);
    }
    else
    {
        delete sprite;
    }
    return;
}

//
void GUICache::cacheSprite(Sprite *sprite)
{
    if( _mobCache.size() < MAX_CACHED_ITEMS )
    {
        _mobCache.push_back(sprite);
    }
    else
    {
        delete sprite;
    }
    return;
}

//
bool GUICache::cacheEffect(Sprite *sprite)
{
    if( _effectCache.size() < MAX_CACHED_ITEMS )
    {
        sprite->setVisible(false);
        sprite->setPosition( ccp(0, 0) );
        _effectCache.push_back(sprite);
        return true;
    }
    return false;
}


//
void GUICache::cacheBomb(Sprite *sprite)
{
    if( _bombCache.size() < MAX_CACHED_ITEMS )
    {
        _bombCache.push_back(sprite);
    }
    else
    {
        delete sprite;
    }
    return;
}

//
Sprite *GUICache::getObstacle()
{
    Sprite *result;
    if( !_obstacleCache.empty() )
    {
        result = _obstacleCache.back();
        _obstacleCache.pop_back();
    }
    else
    {
        result = _creator->createObstacle();
    }
    return result;
}

//
Sprite *GUICache::getSprite()
{
    Sprite *result;
    if( !_mobCache.empty() )
    {
        result = _mobCache.back();
        _mobCache.pop_back();
    }
    else
    {
        result = _creator->createSprite();
    }
    return result;
}

//
Sprite *GUICache::getEffect(Texture2D *texture, Rect rect)
{
    Sprite *effect;
    if( !_effectCache.empty() )
    {
        effect = _effectCache.back();
        _effectCache.pop_back();
        effect->setTextureRect( rect );
        effect->setVisible(true);
    }
    else
    {
        effect = _creator->createEffect(texture, rect);
        // Add to Batch Node
        _batchNode->addChild(effect);
    }
    return effect;   
}

//
Sprite *GUICache::getBomb()
{
    Sprite *result;
    if( !_bombCache.empty() )
    {
        result = _bombCache.back();
        _bombCache.pop_back();
    }
    else
    {
        result = _creator->createBomb();
    }
    return result;
}

void GUICache::resetSprites()
{
    _obstacleCache.clear();
    _mobCache.clear();
    _effectCache.clear();
    _bombCache.clear();
}

//
void GUICache::setBatchNode(SpriteBatchNode* batchNode)
{
    _batchNode = batchNode;
}