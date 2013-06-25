#ifndef __BOMBER_GAME_STATE_LAYER
#define __BOMBER_GAME_STATE_LAYER

#include <deque>
#include <vector>
#include <set>
#include <map>

#include "ExplodableObject.h"
#include "GameStateChange.h"

namespace Bomber
{
    namespace Backend
    {
        class GameStateLayer
        {
            public:
                GameStateLayer(int width, int height);
                void addObject(GameObject *object);
                void addObject(unsigned int id, GameObject *object);
                GameObject *getObject(unsigned int id);
                void removeObject(GameObject *object);
                void removeObject(unsigned int id);
                void getObjectsAroundCoords(Coordinates coords, int range, std::vector<GameObject *> &objects);
                void getObjectsAroundCoords(Coordinates coords, std::vector<GameObject *> &objects);
                void getObjectsAtCoords(Coordinates coords, std::vector<GameObject *> &objects);
                std::map<unsigned int, GameObject *> &getObjects() { return _objects; };

            private:
                int _width;
                int _height;
                std::vector< std::set<GameObject *> > _grid;
                std::map<unsigned int, GameObject *> _objects;
        };
    }
}

#endif
