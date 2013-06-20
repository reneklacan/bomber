/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Logic
 */

#include "Sender.h"

//
void Sender::init()
{
    while(!_logic->isLogicReady()) {
        sleep(0.2);
    }
    while(1) {
        std::map<unsigned int, Point *> &pP = _logic->getPlayersPositions();
        std::cout << "Sender: " << "Player (" << 58585 << "): " << pP[58585]->x << " " << pP[58585]->y << std::endl;
        sleep(1);
    }
    return;
}

//
void Sender::setLogic(Logic *logic)
{
    _logic = logic;
}