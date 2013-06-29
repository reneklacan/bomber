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
                GameStateLayer(const char *name, int width, int height);
                void updateGrid();
                void addObject(GameObject *object);
                void addObject(unsigned int id, GameObject *object);
                GameObject *getObject(unsigned int id);
                void removeObject(GameObject *object);
                void removeObject(unsigned int id);
                std::vector<GameObject *> getObjectsAroundCoords(Coordinates coords, int range);
                std::vector<GameObject *> getObjectsAroundCoords(Coordinates coords);
                std::vector<GameObject *> getObjectsAtCoords(Coordinates coords);
                std::vector<GameObject *> getObjectsAtCoords(unsigned int x, unsigned int y);
                std::map<unsigned int, GameObject *> &getObjects() { return _objects; };
                void print();

            private:
                const char *_name;
                int _width;
                int _height;
                std::vector< std::set<GameObject *> > _grid;
                std::map<unsigned int, GameObject *> _objects;
                std::map<unsigned int, std::set<unsigned int> > _objectGridMap;
        };
    }
}

#endif
