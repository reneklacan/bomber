#ifndef __BOMBER_GAME_STATE_LAYER
#define __BOMBER_GAME_STATE_LAYER

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
                void removeObject(GameObject *object);
                void removeObject(unsigned int id);
                void update(GameStateChange *change);
                void getObjectsAroundCoords(Coordinates coords, std::vector<GameObject *> &objects);

            private:
                int _width;
                int _height;
                std::vector< std::set<GameObject *> > _grid;
                std::map<unsigned int, GameObject *> _objects;
        };
    }
}

#endif
