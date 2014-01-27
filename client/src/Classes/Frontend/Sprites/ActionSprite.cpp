#include "ActionSprite.h"

ActionSprite::ActionSprite(Texture2D *texture, Rect defaultImage)
: _defaultImage(defaultImage), _step(1), _counter(1), _stepImage(0), _upHill(true)
{
    this->initWithTexture(texture, defaultImage);
    _position = ccp(0,0);
}

void ActionSprite::spawnPosition(Point spawnPosition)
{
    _position = spawnPosition;
    this->setPosition(_position);
}

void ActionSprite::updatePosition(Point newPosition)
{
    changeRotation(newPosition);

    _position = newPosition;
    this->setPosition(_position);

    _counter = (_counter + 1) % STEP_CHANGE_RATE;
}

void ActionSprite::updateDefaultImage(Rect newImage)
{
   _defaultImage = newImage;
}

void ActionSprite::changeRotation(Point pNew)
{
    if(_counter == 0) {
        _stepImage = (-1+_step)*TEXTURE_TILE_WIDTH;
    }

    if(_position.x == pNew.x)
    {
        if(_position.y > pNew.y)
        {
            this->setTextureRect(
                CCRectMake (
                    _defaultImage.getMinX()+_stepImage,
                    _defaultImage.getMinY(),
                    TEXTURE_TILE_WIDTH,
                    TEXTURE_TILE_HEIGHT
                )
            );
        }
        else
        {
            this->setTextureRect(
                CCRectMake (
                    _defaultImage.getMinX()+_stepImage,
                    _defaultImage.getMinY()+3*TEXTURE_TILE_HEIGHT,
                    TEXTURE_TILE_WIDTH,
                    TEXTURE_TILE_HEIGHT
                )
            );
        }
    }
    else
    {
        if(_position.x > pNew.x)
        {
            this->setTextureRect(
                CCRectMake (
                    _defaultImage.getMinX()+_stepImage,
                    _defaultImage.getMinY()+TEXTURE_TILE_HEIGHT,
                    TEXTURE_TILE_WIDTH,
                    TEXTURE_TILE_HEIGHT
                )
            );
        }
        else
        {
            this->setTextureRect(
                CCRectMake (
                    _defaultImage.getMinX()+_stepImage,
                    _defaultImage.getMinY()+2*TEXTURE_TILE_HEIGHT,
                    TEXTURE_TILE_WIDTH,
                    TEXTURE_TILE_HEIGHT
                )
            );
        }
    }
    
    if(_step == 2) { _upHill = false; };
    if(_step == 0) { _upHill = true; };
    (_upHill) ? ++_step : --_step;
}