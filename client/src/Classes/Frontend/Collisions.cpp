#include "Collisions.h"

using namespace Bomber;
using namespace Bomber::Frontend;

//
Collisions::Collisions() :
_skipEval(false),
_OWLeft(33),
_OWRight(36),
_OHTop(10),
_OHBottom(0),
_BWLeft(0),
_BWRight(0),
_BHTop(0),
_BHBottom(0)
{
    _mediator = Backend::Mediator::getInstance();
}

//
void Collisions::skipEval(bool skip)
{
    _skipEval = skip;
}

//
void Collisions::reset()
{
    _skipEval = false;
    _collisionFreeAreas.clear();
}

//
void Collisions::setObstacles(std::map<unsigned int, Sprite *> *obstacles)
{
    _obstacles = obstacles;
}

//
void Collisions::setBombs(std::map<unsigned int, Sprite *> *bombs)
{
    _bombs = bombs;
}

//
void Collisions::setObstacleImmuneToPush(unsigned int id)
{
    _immuneObstacles.push_back(id);
}

//
void Collisions::unsetObstacleImmuneToPush(unsigned int id)
{
    auto idToDelete = std::find(_immuneObstacles.begin(), _immuneObstacles.end(), id );
    if( idToDelete != _immuneObstacles.end())
    {
        _immuneObstacles.erase( idToDelete );
    }
}

//
std::vector<bool> Collisions::eval(GameSprite *sprite)
{
    Point currentPoint = sprite->getPosition();;
    Point nextPoint = sprite->getNextPosition();
    // Init
    std::vector<bool> result;
    result.push_back(false);  // Collision occured
    result.push_back(false);  // Collision on X
    result.push_back(false);  // Collision on Y

    // Partial moves
    Point nextPointX = ccp(nextPoint.x, currentPoint.y);
    Point nextPointY = ccp(currentPoint.x, nextPoint.y);

    // Get move direction
    Common::TDirection directionX = Common::CALM;
    Common::TDirection directionY = Common::CALM;
    if(nextPoint.x - currentPoint.x > 0)
    {
        directionX = Common::RIGHT;
    }
    else if(nextPoint.x - currentPoint.x < 0)
    {
        directionX = Common::LEFT;
    }

    if(nextPoint.y - currentPoint.y > 0)
    {
        directionY = Common::UP;
    }
    else if(nextPoint.y - currentPoint.y < 0)
    {
        directionY = Common::DOWN;
    }

    std::vector<unsigned int> toRemove;
    for(auto freeArea : _collisionFreeAreas)
    {
        auto fa = freeArea.second;
        if( (currentPoint.x - fa->getX()) > 55 ||    // Push left
            (currentPoint.y - fa->getY()) > 55 ||    // Push up
            (fa->getX() - currentPoint.x) > 60 ||    // Push right
            (fa->getY() - currentPoint.y) > 50 )     // Push down
        {
            fa->removePlayer( sprite->getID() );
            if( fa->isEmpty() )
            {
                std::cout << "EMPTY\n";
                toRemove.push_back(freeArea.first);
            }
        }
    }
    for(auto idToRemove : toRemove)
    {
        _collisionFreeAreas.erase(idToRemove);
    }


    // Evaluation
    result[1] = this->evalPartial(sprite, nextPointX, directionX);
    result[2] = this->evalPartial(sprite, nextPointY, directionY);
    result[0] = result[1] || result[2];

    // Return
    return result;
}

//
bool Collisions::evalPartial(GameSprite *sprite, Point nextPoint, Common::TDirection direction)
{
    // Init
    bool result = false;
    bool resultObstacles = false;
    bool resultBombs = false;

    // Skip evaluation
    if(_skipEval)
    {
        return result;
    }
    
    // Evaluate all possible items
    resultObstacles = this->evalObstacles(sprite, nextPoint, direction); 
    resultBombs = this->evalBombs(sprite, nextPoint, direction);
    result = resultObstacles || resultBombs;

    return result;
}

//
Sprite *Collisions::getBombAtPosition(int x, int y, unsigned int playerID)
{
    Sprite *result = NULL;
    for(auto bomb : (*_bombs))
    {
        Point pos = bomb.second->getPosition();
        if( ((int)pos.x/TILE_WIDTH == x) && ((int)pos.y/TILE_HEIGHT == y) )
        {
            auto area = _collisionFreeAreas.find(bomb.first);
            if(area == _collisionFreeAreas.end())
            {
                result = dynamic_cast<Sprite *>(bomb.second);
                return result;
            }
            else
            {
                if( !area->second->playerInArea(playerID) )
                {
                    result = dynamic_cast<Sprite *>(bomb.second);
                    return result;
                }
            }
        }
    }
    return result;
}

//
void Collisions::setCFA(unsigned int id, CollisionArea *area)
{
    _collisionFreeAreas[ id ] = area;
}

//
void Collisions::setMapDimensions(unsigned int width, unsigned int height)
{
    _mapWidth = width;
    _mapHeight = height;
}

//
bool Collisions::evalObstacles(GameSprite *sprite, Point nextPoint, Common::TDirection direction)
{
    // TODO: put these 4 code blocks into one cycle with common code to reduce repeating
    //       calculate 4 offsets as points and put them into the vector or so

    bool result = false;
    int offsetX = 0;
    int offsetY = 0;

    // Top Left
    offsetX = (nextPoint.x - _OWLeft) / TILE_WIDTH;
    offsetY = (nextPoint.y + _OHTop) / TILE_HEIGHT;
    unsigned int id = _mapWidth * (_mapHeight - offsetY -1) + offsetX;
    auto obstacle = _obstacles->find( id );
    if( obstacle != _obstacles->end())
    {
        if( std::find(_immuneObstacles.begin(), _immuneObstacles.end(), id ) == _immuneObstacles.end() )
        {
            Common::Coordinates coords = Common::Coordinates(
                obstacle->second->getPosition().x / TILE_WIDTH,
                obstacle->second->getPosition().y / TILE_HEIGHT
            );
            _mediator->pushObstacle(sprite->getID(), coords, direction);
        }
        result = true;
    }
    // Top Right
    offsetX = (nextPoint.x + _OWRight) / TILE_WIDTH;
    id = _mapWidth * (_mapHeight - offsetY -1) + offsetX;
    obstacle = _obstacles->find( id );
    if( obstacle != _obstacles->end())
    {
        if( std::find(_immuneObstacles.begin(), _immuneObstacles.end(), id ) == _immuneObstacles.end() )
        {
            Common::Coordinates coords = Common::Coordinates(
                obstacle->second->getPosition().x / TILE_WIDTH,
                obstacle->second->getPosition().y / TILE_HEIGHT
            );
            _mediator->pushObstacle(sprite->getID(), coords, direction);
        }
        result = true;
    }

    // Bottom Left
    offsetX = (nextPoint.x - _OWLeft) / TILE_WIDTH;
    offsetY = (nextPoint.y - _OHBottom) / TILE_HEIGHT;
    id = _mapWidth * (_mapHeight - offsetY -1) + offsetX;
    obstacle = _obstacles->find( id );
    if( obstacle != _obstacles->end())
    {
        if( std::find(_immuneObstacles.begin(), _immuneObstacles.end(), id ) == _immuneObstacles.end() )
        {
            Common::Coordinates coords = Common::Coordinates(
                obstacle->second->getPosition().x / TILE_WIDTH,
                obstacle->second->getPosition().y / TILE_HEIGHT
            );
            _mediator->pushObstacle(sprite->getID(), coords, direction);
        }
        result = true;
    }

    // Bottom Right
    offsetX = (nextPoint.x + _OWRight) / TILE_WIDTH;
    id = _mapWidth * (_mapHeight - offsetY -1) + offsetX;
    obstacle = _obstacles->find( id );
    if( obstacle != _obstacles->end())
    {
        if( std::find(_immuneObstacles.begin(), _immuneObstacles.end(), id ) == _immuneObstacles.end() )
        {
            Common::Coordinates coords = Common::Coordinates(
                obstacle->second->getPosition().x / TILE_WIDTH,
                obstacle->second->getPosition().y / TILE_HEIGHT
            );
            _mediator->pushObstacle(sprite->getID(), coords, direction);
        }
        result = true;
    }

    return result;
}

//
//
bool Collisions::evalBombs(GameSprite *sprite, Point nextPoint, Common::TDirection direction)
{
    bool result = false;
    int offsetX = 0;
    int offsetY = 0;

    // Top Left
    offsetX = (nextPoint.x - _BWLeft) / TILE_WIDTH;
    offsetY = (nextPoint.y + _BHTop) / TILE_HEIGHT;
    auto bomb = this->getBombAtPosition(offsetX, offsetY, sprite->getID());
    if( bomb != NULL)
    {
        Common::Coordinates coords = Common::Coordinates(
            bomb->getPosition().x / TILE_WIDTH,
            bomb->getPosition().y / TILE_HEIGHT
        );
        _mediator->kickBomb(sprite->getID(), coords, direction);
        result = true;
    }
    // Top Right
    offsetX = (nextPoint.x + _BWRight) / TILE_WIDTH;
    bomb = this->getBombAtPosition(offsetX, offsetY, sprite->getID());
    if( bomb != NULL)
    {
        Common::Coordinates coords = Common::Coordinates(
            bomb->getPosition().x / TILE_WIDTH,
            bomb->getPosition().y / TILE_HEIGHT
        );
        _mediator->kickBomb(sprite->getID(), coords, direction);
        result = true;
    }

    // Bottom Left
    offsetX = (nextPoint.x - _BWLeft) / TILE_WIDTH;
    offsetY = (nextPoint.y - _BHBottom) / TILE_HEIGHT;
    bomb = this->getBombAtPosition(offsetX, offsetY, sprite->getID());
    if( bomb != NULL)
    {
        Common::Coordinates coords = Common::Coordinates(
            bomb->getPosition().x / TILE_WIDTH,
            bomb->getPosition().y / TILE_HEIGHT
        );
        _mediator->kickBomb(sprite->getID(), coords, direction);
        result = true;
    }

    // Bottom Right
    offsetX = (nextPoint.x + _BWRight) / TILE_WIDTH;
    bomb = this->getBombAtPosition(offsetX, offsetY, sprite->getID());
    if( bomb != NULL)
    {
        Common::Coordinates coords = Common::Coordinates(
            bomb->getPosition().x / TILE_WIDTH,
            bomb->getPosition().y / TILE_HEIGHT
        );
        _mediator->kickBomb(sprite->getID(), coords, direction);
        result = true;
    }

    return result;
}