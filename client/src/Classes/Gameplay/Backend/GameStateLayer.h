#ifndef __BOMBER_GAME_STATE_LAYER
#define __BOMBER_GAME_STATE_LAYER

#include <stdio.h>
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
        template <class ObjectType>
        class GameStateLayer
        {
            public:
                GameStateLayer(const char *name, int width, int height);
                void updateGrid();
                void reset();
                void addObject(ObjectType *object);
                void addObject(unsigned int id, ObjectType *object);
                ObjectType *getObject(unsigned int id);
                void removeObject(ObjectType *object);
                void removeObject(unsigned int id);
                std::vector<ObjectType *> getObjectsAroundCoords(Coordinates coords, int range);
                std::vector<ObjectType *> getObjectsAroundCoords(Coordinates coords);
                std::vector<ObjectType *> getObjectsAtCoords(Coordinates coords);
                std::vector<ObjectType *> getObjectsAtCoords(unsigned int x, unsigned int y);
                std::map<unsigned int, ObjectType *> &getObjects() { return _objects; };
                void print();

            private:
                const char *_name;
                unsigned int _width;
                unsigned int _height;
                unsigned int _gridSize;
                std::vector< std::set<ObjectType *> > _grid;
                std::map<unsigned int, ObjectType *> _objects;
                std::map<unsigned int, std::set<unsigned int> > _objectGridMap;
        };

        template <class ObjectType>
        GameStateLayer<ObjectType>::GameStateLayer(const char *name, int width, int height)
        {
            _name = name;
            _width = width;
            _height = height;
            _gridSize = width*height;

            for (unsigned int i = 0; i < _gridSize; i++)
            {
                std::set<ObjectType *> s;
                _grid.push_back(s);
            }
        }

        template <class ObjectType>
        void GameStateLayer<ObjectType>::reset()
        {
            // TODO: unallocate GameObjects that we are going to clear
            /*
            for (auto pair : this->getObjects())
            {
                delete pair.second;
            }
            */

            _grid.clear();
            _objects.clear();
            _objectGridMap.clear();

            for (int i = 0; i < _gridSize; i++)
            {
                std::set<ObjectType *> s;
                _grid.push_back(s);
            }
        }

        template <class ObjectType>
        void GameStateLayer<ObjectType>::updateGrid()
        {
            for (auto pair : _objects)
            {
                auto object = pair.second;

                if (object->isDirty())
                {
                    object->setDirty(false);

                    for (unsigned int index : _objectGridMap[object->getId()])
                    {
                        _grid[index].erase(object);
                    }

                    Coordinates coords = object->getCoords();
                    unsigned int newIndex = coords.y*_width + coords.x;

                    _objectGridMap[object->getId()].clear();
                    _objectGridMap[object->getId()].insert(newIndex);

                    _grid[newIndex].insert(object);
                }
            }
        }

        template <class ObjectType>
        void GameStateLayer<ObjectType>::addObject(ObjectType *object)
        {
            this->addObject(object->getId(), object);
        }

        template <class ObjectType>
        void GameStateLayer<ObjectType>::addObject(unsigned int id, ObjectType *object)
        {
            _objects[id] = object;

            Coordinates coords = object->getCoords();
            //printf("addObject at x:%d y:%d with id %d\n", coords.x, coords.y, id);
            _objectGridMap[id].insert(coords.y*_width + coords.x);
            _grid[coords.y*_width + coords.x].insert(object);
        }

        template <class ObjectType>
        ObjectType *GameStateLayer<ObjectType>::getObject(unsigned int id)
        {
            return _objects[id];
        }

        template <class ObjectType>
        void GameStateLayer<ObjectType>::removeObject(ObjectType *object)
        {
            Coordinates coords = object->getCoords();
            _grid[coords.y*_width + coords.x].erase(object);
            _objects.erase(_objects.find(object->getId()));
        }

        template <class ObjectType>
        void GameStateLayer<ObjectType>::removeObject(unsigned int id)
        {
            //printf("xxxxxxxxx remove object with id %d\n", id);
            _objects.erase(_objects.find(id));
        }

        template <class ObjectType>
        std::vector<ObjectType *> GameStateLayer<ObjectType>::getObjectsAroundCoords(Coordinates coords, int range)
        {
            std::vector<ObjectType *> objects;

            for (int y = coords.y - range; y <= coords.y + range; y++)
            {
                for (int x = coords.x - range; x <= coords.x + range; x++)
                {
                    if (x < 0 || x >= _width || y < 0 || y >= _height)
                        continue;

                    for (ObjectType *object : _grid[y*_width + x])
                    {
                        objects.push_back(object);
                    }
                }
            }

            return objects;
        }

        template <class ObjectType>
        std::vector<ObjectType *> GameStateLayer<ObjectType>::getObjectsAroundCoords(Coordinates coords)
        {
            return this->getObjectsAroundCoords(coords, 1);
        }

        template <class ObjectType>
        std::vector<ObjectType *> GameStateLayer<ObjectType>::getObjectsAtCoords(Coordinates coords)
        {
            return this->getObjectsAroundCoords(coords, 0);
        }

        template <class ObjectType>
        std::vector<ObjectType *> GameStateLayer<ObjectType>::getObjectsAtCoords(unsigned int x, unsigned int y)
        {
            return this->getObjectsAroundCoords(Coordinates(x, y), 0);
        }

        template <class ObjectType>
        void GameStateLayer<ObjectType>::print()
        {
            printf("%s\n", _name);
            printf("----------\n");
            
            for (int iy = _height - 1; iy >= 0; iy--)
            {
                for (int ix = 0; ix < _width; ix++)
                {
                    printf("%lu ", this->getObjectsAtCoords(ix, iy).size());
                }
                printf("\n");
            }

            printf("----------\n");
}
    }
}

#endif
