#ifndef __BOMBER_GAME_STATE_LAYER
#define __BOMBER_GAME_STATE_LAYER

#include <vector>
#include <set>

#include "GameObject.h"
#include "GameStateChange.h"
#include "GameObjectEventDelegate.h"

class GameStateLayer : public GameObjectEventDelegate
{
    public:
        GameStateLayer(int width, int height);
        void addObject(GameObject *object);
        void removeObject(GameObject *object);
        void update(GameStateChange *change);
        void getObjectsAroundCoords(Coordinates coords, std::vector<GameObject *> &objects);

    private:
        int _width;
        int _height;
        std::vector< std::set<GameObject *> > _grid;
        std::set<GameObject *> _objects;
};

#endif
