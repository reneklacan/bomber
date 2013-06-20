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

#include "../Comm/Communication.h"
#include "../Map/Map.h"
#include "cocos2d.h"

enum GAME_LEVELS {
    DEFAULT
};

class Logic
{
public:
    Logic() {};
    ~Logic() {};

    void init();
    void updateState(std::vector<unsigned char> data);

private:
    std::map<unsigned int, CCPoint> _playersPositions;
    std::map<unsigned int, CCPoint> _bombsPositions;
    std::vector<std::vector<CCPoint> > _obstacles;

    void initGame(GAME_LEVELS gameID);
    void processMovement(unsigned int pid, unsigned int p_x, unsigned int p_y);

};

#endif