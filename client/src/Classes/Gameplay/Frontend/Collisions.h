#ifndef __BOMBER_FRONTEND_COLLISIONS
#define __BOMBER_FRONTEND_COLLISIONS

#include "cocos2d.h"

#include "../Backend/Mediator.h"
#include "../Backend/Primitives/Direction.h"
#include "../../Input/ControlLayer.h"
#include "../../Constants.h"

namespace Bomber
{
    namespace Frontend
    {
        class Collisions
        {
        public:
        	Collisions();

        	void setObstacles(std::map<unsigned int, Sprite *> *obstacles);
        	void setBombs(std::map<unsigned int, Sprite *> *bombs);
        	void setMapDimensions(unsigned int width, unsigned int height);
        	std::vector<bool> eval(Point currentPoint, Point nextPoint);
        	void skipEval(bool skip);
        	void setCFA(unsigned int id, Point point);
        	void reset();

        private:
        	bool evalObstacles(Point nextPoint, Backend::TDirection direction);
        	bool evalBombs(Point nextPoint, Backend::TDirection direction);
        	bool evalPartial(Point nextPoint, Backend::TDirection direction);
        	Sprite *getBombAtPosition(int x, int y);

        	bool _skipEval;
        	int _OWLeft;	// Obstacle collision Width area Left
        	int _OWRight;
        	int _OHTop;	// Obstacle collision Height area Top
        	int _OHBottom;
        	int _BWLeft;	// Bomb collision Width area Left
        	int _BWRight;
        	int _BHTop;	// Bomb collision Height area Top
        	int _BHBottom;
        	Backend::Mediator* _mediator;
        	std::map<unsigned int, Sprite *> *_obstacles;
        	std::map<unsigned int, Sprite *> *_bombs;
        	std::map<unsigned int, Point> _collisionFreeAreas;
        	unsigned int _mapWidth;
        	unsigned int _mapHeight;

        };
    }
}

#endif