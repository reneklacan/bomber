/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Logic
 */

#ifndef __BOMBER_LOGIC_LAYER
#define __BOMBER_LOGIC_LAYER

#include <iostream>
#include <vector>
#include <map>
#include <sstream>

#include "../Comm/Protocol_v1.h"
#include "tinyxml2.h"

 using namespace tinyxml2;

enum GAME_LEVELS {
    DEFAULT
};

enum GAME_LAYER_OBJECTS {
    BUGS = 13,
    PORTAL = 15,
    HORIZONT = 20,
    HIGH_BARRIER = 41,
    LOW_BARRIER = 42
};

class Point
{
public:
    Point(int X, int Y): x(X), y(Y) {}
    ~Point() {}

    int x;
    int y;
};

class Logic
{
public:
    Logic(): _isReady(false)
    {
        _protocol = new Protocol_v1();
    };
    ~Logic() {};

    void init();
    void updateState(std::vector<unsigned char> data);
    std::map<unsigned int, Point *> &getPlayersPositions();
    bool isLogicReady()
    {
        return _isReady;
    }

private:
    bool _isReady;
    Protocol_v1 *_protocol;

    std::map<unsigned int, Point *> _playersPositions;
    std::map<unsigned int, Point *> _bombsPositions;
    std::map<Point *, GAME_LAYER_OBJECTS> _obstacles;
    std::map<Point *, GAME_LAYER_OBJECTS> _portals;
    std::map<Point *, GAME_LAYER_OBJECTS> _items;

    void initGame(GAME_LEVELS gameID);
    void initLayer(XMLElement* element, std::map<Point *, GAME_LAYER_OBJECTS> &structure);
    void processMovement(unsigned int pid, unsigned int p_x, unsigned int p_y);
    void processPlanting(unsigned int pid, unsigned int p_x, unsigned int p_y);

};

#endif