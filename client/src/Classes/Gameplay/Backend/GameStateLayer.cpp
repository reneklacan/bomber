
#include "GameStateLayer.h"
#include <stdio.h>

using namespace Bomber::Backend;

GameStateLayer::GameStateLayer(int width, int height)
{
    _width = width;
    _height = height;
    int gridSize = width*height;

    for (int i = 0; i < gridSize; i++)
    {
        std::set<GameObject *> s;
        _grid.push_back(s);
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
    printf("%d %d\n", coords.x, coords.y);
    printf("%d %d %d\n", _width, _height, coords.y*_width + coords.x);
    _grid[coords.y*_width + coords.x].insert(object);
}

GameObject *GameStateLayer::getObject(unsigned int id)
{
    return _objects.at(id);
}

void GameStateLayer::removeObject(GameObject *object)
{
    this->removeObject(object->getId());
}

void GameStateLayer::removeObject(unsigned int id)
{
    _objects.erase(_objects.find(id));
}

void GameStateLayer::getObjectsAroundCoords(Coordinates coords, int range, std::vector<GameObject *> &objects)
{
    for (int y = coords.y - range; y <= coords.y + range; y++)
    {
        for (int x = coords.x - range; x <= coords.x + range; x++)
        {
            for (GameObject *object : _grid[y*_width + x])
            {
                objects.push_back(object);
            }
        }
    }
}

void GameStateLayer::getObjectsAroundCoords(Coordinates coords, std::vector<GameObject *> &objects)
{
    this->getObjectsAroundCoords(coords, 1, objects);
}

void GameStateLayer::getObjectsAtCoords(Coordinates coords, std::vector<GameObject *> &objects)
{
    this->getObjectsAroundCoords(coords, 0, objects);
}

