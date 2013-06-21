/*
 * Project: Bomber
 * Created: 21.06.2013
 * Class: Protocol_v1
 */

#include "Protocol_v1.h"

//
void Protocol_v1::setDataPlayerAction(std::vector<unsigned char> &buffer, TPlayerAction *data)
{
    // Set Session ID
    buffer.push_back( (unsigned char)(data->session_id / 256) );
    buffer.push_back( (unsigned char)(data->session_id % 256) );
    // Set Player ID
    buffer.push_back( (unsigned char)(data->player_id / 256) );
    buffer.push_back( (unsigned char)(data->player_id % 256) );
    // Set Type of Data
    buffer.push_back( (unsigned char)(data->action_type) );
    // Set Location X
    buffer.push_back( (unsigned char)(data->location_x / 256) );
    buffer.push_back( (unsigned char)(data->location_x % 256) );
    // Set Location Y
    buffer.push_back( (unsigned char)(data->location_y / 256) );
    buffer.push_back( (unsigned char)(data->location_y % 256) );

    return;
}

//
bool Protocol_v1::getDataPlayerAction(TPlayerAction *playerAction, std::vector<unsigned char> &data)
{
    if(data.size() != PLAYER_ACTION_PAKET_LENGTH) {
        std::cerr << "Wrong length of received packet: " << data.size() << std::endl;
        return false;
    }

    playerAction->session_id = data[0] * 256 + data[1];
    playerAction->player_id = data[2] * 256 + data[3];
    playerAction->action_type = (SEND_PACKET_TYPES)data[4];
    playerAction->location_x = data[5] * 256 + data[6];
    playerAction->location_y = data[7] * 256 + data[8];

    return true;
}