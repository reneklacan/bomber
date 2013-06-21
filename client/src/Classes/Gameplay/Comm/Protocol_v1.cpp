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

//
void Protocol_v1::setDataServerSync(std::vector<unsigned char> &buffer, TServerSync &data)
{
    buffer.push_back( (unsigned char)(data.session_id / 256) );
    buffer.push_back( (unsigned char)(data.session_id % 256) );
    buffer.push_back( (unsigned char)(data.num_players / 256) );
    buffer.push_back( (unsigned char)(data.num_players % 256) );
    for(std::vector<TServerPlayer>::iterator it = data.players_data.begin(); it != data.players_data.end(); it++)
    {
        buffer.push_back( (unsigned char)(it->data_length / 256) );
        buffer.push_back( (unsigned char)(it->data_length % 256) );
        buffer.push_back( (unsigned char)(it->player_id / 256) ); 
        buffer.push_back( (unsigned char)(it->player_id % 256) ); 
        buffer.push_back( (unsigned char)(it->player_state) ); 
        buffer.push_back( (unsigned char)(it->location_x / 256) );
        buffer.push_back( (unsigned char)(it->location_x % 256) );
        buffer.push_back( (unsigned char)(it->location_y / 256) );
        buffer.push_back( (unsigned char)(it->location_y % 256) ); 
    }

    return;
}

//
bool Protocol_v1::getDataServerSync(TServerSync *target, std::vector<unsigned char> *workData)
{
    unsigned int dataSize = workData->size();
    if(dataSize < MINIMUM_SERVER_SYNC_PAKET_LENGTH)
    {
        std::cerr << "1: Wrong length of received packet: " << workData->size() << std::endl;
        return false;
    }

    std::vector<unsigned char> &data = *workData;

    target->session_id = data[0] * 256 + data[1];
    target->num_players = data[2] * 256 + data[3];
    unsigned int offset = 4;
    dataSize -= MINIMUM_SERVER_SYNC_PAKET_LENGTH;
    for(unsigned int i = 0; i < target->num_players; i++)
    {
        if(dataSize < 2) {
            std::cerr << "2: Wrong length of received packet: " << workData->size() << std::endl;
            return false;
        }

        TServerPlayer sP;
        sP.data_length = data[offset] * 256 + data[offset+1];
        offset += 2;
        if(dataSize < sP.data_length) {
            std::cerr << "3: Wrong length of received packet: " << workData->size() << std::endl;
            return false;
        }

        sP.player_id = data[offset] * 256 + data[offset+1];
        offset += 2;
        sP.player_state = data[offset];
        offset += 1;
        sP.location_x = data[offset] * 256 + data[offset+1];
        offset += 2;
        sP.location_y = data[offset] * 256 + data[offset+1];
        offset += 2;

        target->players_data.push_back(sP);

        dataSize -= sP.data_length;
    }

    return true;
}