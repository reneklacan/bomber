/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Logic
 */

#include "Sender.h"
#include "../Comm/Sockets.h"
#include "../Comm/Protocol_v1.h"

std::vector<unsigned char> Sender::init()
{
    // Get player positions
    std::map<unsigned int, Point *> &pP = _logic->getPlayersPositions();

    // Inicialize data structure
    _data.session_id = 14568; // TODO
    _data.num_players = pP.size();
    for(std::map<unsigned int, Point *>::iterator it = pP.begin(); it != pP.end(); it++)
    {
        TServerPlayer sP = 
        {
            PLAYER_ACTION_PAKET_LENGTH,
            it->first,
            0, // TODO
            it->second->x,
            it->second->y
        };
        _data.players_data.push_back(sP);
    }

    // Create packet
    _protocol->setDataServerSync(_buffer, _data);

    // DEBUG
    //std::cout << "Sender: " << "Player (" << 58585 << "): " << pP[58585]->x << " " << pP[58585]->y << std::endl;

    return _buffer;
}

//
void Sender::setLogic(Logic *logic)
{
    _logic = logic;
}