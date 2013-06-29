
#include "GameStateLayer.h"
#include <stdio.h>

using namespace Bomber::Backend;

GameStateLayer::GameStateLayer(const char *name, int width, int height)
{
    _name = name;
    _width = width;
    _height = height;
    int gridSize = width*height;

    for (int i = 0; i < gridSize; i++)
    {
        std::set<GameObject *> s;
        _grid.push_back(s);
    }
}

void GameStateLayer::updateGrid()
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

void GameStateLayer::addObject(GameObject *object)
{
    this->addObject(object->getId(), object);
}

void GameStateLayer::addObject(unsigned int id, GameObject *object)
{
    _objects[id] = object;

    Coordinates coords = object->getCoords();
    //printf("addObject at x:%d y:%d with id %d\n", coords.x, coords.y, id);
    _objectGridMap[id].insert(coords.y*_width + coords.x);
    _grid[coords.y*_width + coords.x].insert(object);
}

GameObject *GameStateLayer::getObject(unsigned int id)
{
    return _objects[id];
}

void GameStateLayer::removeObject(GameObject *object)
{
    Coordinates coords = object->getCoords();
    _grid[coords.y*_width + coords.x].erase(object);
    _objects.erase(_objects.find(object->getId()));
}

void GameStateLayer::removeObject(unsigned int id)
{
    //printf("xxxxxxxxx remove object with id %d\n", id);
    _objects.erase(_objects.find(id));
}

std::vector<GameObject *> GameStateLayer::getObjectsAroundCoords(Coordinates coords, int range)
{
    std::vector<GameObject *> objects;

    for (int y = coords.y - range; y <= coords.y + range; y++)
    {
        for (int x = coords.x - range; x <= coords.x + range; x++)
        {
            if (x < 0 || x >= _width || y < 0 || y >= _height)
                continue;

            for (GameObject *object : _grid[y*_width + x])
            {
                objects.push_back(object);
            }
        }
    }

    return objects;
}

std::vector<GameObject *> GameStateLayer::getObjectsAroundCoords(Coordinates coords)
{
    return this->getObjectsAroundCoords(coords, 1);
}

std::vector<GameObject *> GameStateLayer::getObjectsAtCoords(Coordinates coords)
{
    return this->getObjectsAroundCoords(coords, 0);
}

std::vector<GameObject *> GameStateLayer::getObjectsAtCoords(unsigned int x, unsigned int y)
{
    return this->getObjectsAroundCoords(Coordinates(x, y), 0);
}

void GameStateLayer::print()
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
