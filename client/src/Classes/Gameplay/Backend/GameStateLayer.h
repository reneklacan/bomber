#ifndef __BOMBER_GAME_STATE_LAYER
#define __BOMBER_GAME_STATE_LAYER

#include <deque>
#include <vector>
#include <set>
#include <map>

#include "GameObject.h"
#include "GameStateChange.h"
#include "GameObjectEventDelegate.h"

namespace Bomber
{
    namespace Backend
    {
        class GameStateLayer : public GameObjectEventDelegate
        {
            public:
                GameStateLayer(int width, int height);
                void addObject(GameObject *object);
                void addObject(unsigned int id, GameObject *object);
                GameObject *getObject(unsigned int id);
                void removeObject(GameObject *object);
                void removeObject(unsigned int id);
                void update(GameStateChange *change);
                void getObjectsAroundCoords(Coordinates coords, int range, std::vector<GameObject *> &objects);
                void getObjectsAroundCoords(Coordinates coords, std::vector<GameObject *> &objects);
                void getObjectsAtCoords(Coordinates coords, std::vector<GameObject *> &objects);

                std::deque<GameStateChange *> &getChanges() { return _changes; };
                GameStateChange *popChange();

            private:
                int _width;
                int _height;
                std::vector< std::set<GameObject *> > _grid;
                std::map<unsigned int, GameObject *> _objects;
                std::deque<GameStateChange *> _changes;
        };
    }
}

#endif
