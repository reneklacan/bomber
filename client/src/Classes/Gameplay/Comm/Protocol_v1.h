/*
 * Project: Bomber
 * Created: 21.06.2013
 * Class: Protocol_v1
 */

#ifndef __BOMBER_PROTOCOL_V1_LAYER
#define __BOMBER_PROTOCOL_V1_LAYER

#include <vector>
#include <iostream>

#define PLAYER_ACTION_PAKET_LENGTH 9 // number of Bytes

// Types of packets for sending to a server
enum SEND_PACKET_TYPES {
    MOVE,
    PLANT
};

typedef struct {
    SEND_PACKET_TYPES action_type;
    unsigned int session_id;
    unsigned int player_id;
    unsigned int location_x;
    unsigned int location_y;
} TPlayerAction;

class Protocol_v1
{
public:
    Protocol_v1() {}
    ~Protocol_v1() {}

    void setDataPlayerAction(std::vector<unsigned char> &buffer, TPlayerAction *data);
    bool getDataPlayerAction(TPlayerAction *playerAction, std::vector<unsigned char> &data);

private:
};

#endif