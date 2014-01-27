#include "ActionSprite.h"

ActionSprite::ActionSprite(Texture2D *texture, Rect defaultImage)
: _defaultImage(defaultImage), _step(1), _counter(1), 
_stepImage(0), _upHill(true),
_speed(50), _isAlive(true)
{
    this->initWithTexture(texture, defaultImage);
    _position = ccp(0,0);
    _speed = 100;
}

void ActionSprite::spawnPosition(Point spawnPosition)
{
    _position = spawnPosition;
    this->setPosition(_position);

    this->setTextureRect(
        CCRectMake (
            _defaultImage.getMinX(),
            _defaultImage.getMinY(),
            TEXTURE_TILE_WIDTH,
            TEXTURE_TILE_HEIGHT
        )
    );
}

void ActionSprite::updatePosition(Point newPosition)
{
    changeRotation(newPosition);

    _position = newPosition;
    this->setPosition(_position);

    // Threshold algorithm with saturation
    int threshold = STEP_CHANGE_RATE;
    if(_speed > 100)
    {
        threshold = (int)(STEP_CHANGE_RATE - _speed/50);
    }
    else if(_speed < 100)
    {
        threshold = (int)(STEP_CHANGE_RATE + (100-_speed)/8);
    }
    // 20 --- 100 --- 500 : speed
    // 22 <--  12 -->  3 : threshold
    if(threshold < MAX_CHANGE_RATE) { threshold = MAX_CHANGE_RATE; }
    else if(threshold > MIN_CHANGE_RATE) { threshold = MIN_CHANGE_RATE; }

    _counter = (_counter + 1) % threshold;
}

void ActionSprite::updateDefaultImage(Rect newImage)
{
   _defaultImage = newImage;
}

void ActionSprite::resetRotations()
{
    _step = 1; 
    _counter = 1;
}

void ActionSprite::changeRotation(Point pNew)
{
    bool change = false;

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
            change = true;
        }
        else if(_position.y < pNew.y)
        {
            this->setTextureRect(
                CCRectMake (
                    _defaultImage.getMinX()+_stepImage,
                    _defaultImage.getMinY()+3*TEXTURE_TILE_HEIGHT,
                    TEXTURE_TILE_WIDTH,
                    TEXTURE_TILE_HEIGHT
                )
            );
            change = true;
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
            change = true;
        }
        else if(_position.x < pNew.x)
        {
            this->setTextureRect(
                CCRectMake (
                    _defaultImage.getMinX()+_stepImage,
                    _defaultImage.getMinY()+2*TEXTURE_TILE_HEIGHT,
                    TEXTURE_TILE_WIDTH,
                    TEXTURE_TILE_HEIGHT
                )
            );
            change = true;
        }
    }
    
    if(change){
        if(_step == 2) { _upHill = false; }
        if(_step == 0) { _upHill = true; }
        (_upHill) ? ++_step : --_step;
    }
    
}