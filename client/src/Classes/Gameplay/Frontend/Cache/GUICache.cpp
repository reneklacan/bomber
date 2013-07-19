#include "GUICache.h"

using namespace Bomber::Frontend;

//
GUICache *GUICache::getInstance()
{
    static GUICache instance;
    return &instance;
}

//
void GUICache::initCaches(Map* map)
{
    int i;
    _sprites2Spawn = 0;
    _effects2Spawn = 0;

    TMXLayer *sprites2spawnLayer = map->getTiledMap()->layerNamed("sprites2spawn");
    TMXLayer *effects2spawnLayer = map->getTiledMap()->layerNamed("effects2spawn");

    // Get info about sprites and effect to spawn
    for(int ix = 0; ix < map->getWidth(); ix++)
    {
        for(int iy = 0; iy < map->getHeight(); iy++)
        {
            Point point = ccp(ix, iy);
            if(sprites2spawnLayer->tileGIDAt( point ) != 0)
            {
                _sprites2Spawn++;
            }
            if(effects2spawnLayer->tileGIDAt( point ) != 0)
            {
                _effects2Spawn++;
            }
        }
    }

    // IMPORTANT: Batch Node must be initialized before

    // Cache obstacles and bombs
    for(i = 0; i < MAX_CACHED_ITEMS; i++)
    {
        _obstacleCache.push_back( 
            _creator->createObstacle(
                _batchNode->getTexture(),
                Rect(0,0,0,0)
            )
        );
        _obstacleCache.back()->setVisible(false);
        _batchNode->addChild(_obstacleCache.back());

        _bombCache.push_back( 
            _creator->createBomb(
                _batchNode->getTexture(),
                Rect(0,0,0,0)
            )
        );
        _bombCache.back()->setVisible(false);
        _batchNode->addChild(_bombCache.back());
    }

    // Cache mobs
    for(i = 0; i < _sprites2Spawn + MAX_CACHED_ITEMS; i++)
    {
        _mobCache.push_back( 
            _creator->createSprite(
                _batchNode->getTexture(),
                Rect(0,0,0,0)
            )
        );
        _mobCache.back()->setVisible(false);
        _batchNode->addChild(_mobCache.back());
    }

    // Cache effects
    for(i = 0; i < _effects2Spawn + MAX_CACHED_ITEMS; i++)
    {
        _effectCache.push_back( 
            _creator->createEffect(
                _batchNode->getTexture(),
                Rect(0,0,0,0)
            )
        );
        _effectCache.back()->setVisible(false);
        _batchNode->addChild(_effectCache.back());
    }

    return;
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

    // Portals
    TMXLayer *portalsLayer = map->getTiledMap()->layerNamed("portals");

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

            if(portalsLayer->tileGIDAt( point ) != 0)
            {
                int position = map->getWidth() * iy + ix;
                _portals[ position ] = portalsLayer->tileAt( point );
            }

        }
    }
}

//
bool GUICache::cacheObstacle(Sprite * sprite)
{
    if( _obstacleCache.size() < MAX_CACHED_ITEMS )
    {
        sprite->setVisible(false);
        sprite->setPosition( ccp(0, 0) );
        _obstacleCache.push_back(sprite);
        return true;
    }
    return false;
}

//
bool GUICache::cacheSprite(Sprite *sprite)
{
    if( _mobCache.size() < _sprites2Spawn + MAX_CACHED_ITEMS )
    {
        sprite->setVisible(false);
        sprite->setPosition( ccp(0, 0) );
        _mobCache.push_back(sprite);
        return true;
    }
    return false;
}

//
bool GUICache::cacheEffect(Sprite *sprite)
{
    if( _effectCache.size() < _effects2Spawn + MAX_CACHED_ITEMS )
    {
        sprite->setVisible(false);
        sprite->setPosition( ccp(0, 0) );
        _effectCache.push_back(sprite);
        return true;
    }
    return false;
}


//
bool GUICache::cacheBomb(Sprite *sprite)
{
    if( _bombCache.size() < MAX_CACHED_ITEMS )
    {
        sprite->setVisible(false);
        sprite->setPosition( ccp(0, 0) );
        _bombCache.push_back(sprite);
        return true;
    }
    return false;
}

//
Sprite *GUICache::getObstacle(Texture2D *texture, Rect rect)
{
    Sprite *obstacle;
    if( !_obstacleCache.empty() )
    {
        obstacle = _obstacleCache.back();
        _obstacleCache.pop_back();
        obstacle->setTextureRect( rect );
        obstacle->setVisible(true);
    }
    else
    {
        obstacle = _creator->createObstacle(texture, rect);
        // Add to Batch Node
        _batchNode->addChild(obstacle);
    }
    return obstacle;
}

//
Sprite *GUICache::getSprite(Texture2D *texture, Rect rect)
{
    Sprite *mob;
    if( !_mobCache.empty() )
    {
        mob = _mobCache.back();
        _mobCache.pop_back();
        mob->setTextureRect( rect );
        mob->setVisible(true);
    }
    else
    {
        mob = _creator->createSprite(texture, rect);
        // Add to Batch Node
        _batchNode->addChild(mob);
    }
    return mob;
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
Sprite *GUICache::getBomb(Texture2D *texture, Rect rect)
{
    Sprite *bomb;
    if( !_bombCache.empty() )
    {
        bomb = _bombCache.back();
        _bombCache.pop_back();
        bomb->setTextureRect( rect );
        bomb->setVisible(true);
    }
    else
    {
        bomb = _creator->createBomb(texture, rect);
        // Add to Batch Node
        _batchNode->addChild(bomb);
    }
    return bomb;
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