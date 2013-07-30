#ifndef __BOMBER_FRONTEND_COLLISIONS
#define __BOMBER_FRONTEND_COLLISIONS

#include "cocos2d.h"

#include <algorithm>

#include "../Backend/Mediator.h"
#include "../Common/Primitives/Direction.h"
#include "../../Input/ControlLayer.h"
#include "../../Constants.h"
#include "Primitives/CollisionArea.h"

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
            std::vector<bool> eval(GameSprite *sprite);
            void skipEval(bool skip);
            void setCFA(unsigned int id, CollisionArea *area);
            void reset();
            void setObstacleImmuneToPush(unsigned int id);
            void unsetObstacleImmuneToPush(unsigned int id);

        private:
            bool evalObstacles(GameSprite *sprite, Point nextPoint, Common::TDirection direction);
            bool evalBombs(GameSprite *sprite, Point nextPoint, Common::TDirection direction);
            bool evalPartial(GameSprite *sprite, Point nextPoint, Common::TDirection direction);
            Sprite *getBombAtPosition(int x, int y, unsigned int playerID);

            bool _skipEval;
            int _OWLeft;    // Obstacle collision Width area Left
            int _OWRight;
            int _OHTop; // Obstacle collision Height area Top
            int _OHBottom;
            int _BWLeft;    // Bomb collision Width area Left
            int _BWRight;
            int _BHTop; // Bomb collision Height area Top
            int _BHBottom;
            Backend::Mediator* _mediator;
            std::map<unsigned int, Sprite *> *_obstacles;
            std::map<unsigned int, Sprite *> *_bombs;
            std::map<unsigned int, CollisionArea *> _collisionFreeAreas;
            unsigned int _mapWidth;
            unsigned int _mapHeight;
            std::vector<unsigned int> _immuneObstacles;

        };
    }
}

#endif