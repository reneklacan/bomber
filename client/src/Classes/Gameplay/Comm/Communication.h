/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Communication
 */

#ifndef __BOMBER_COMMUNICATION_LAYER
#define __BOMBER_COMMUNICATION_LAYER

#include <string>
#include <iostream>
#include <vector> 
#include <boost/asio.hpp>

#include "Protocol_v1.h"

using namespace std;

class Communication {
public:
    Communication(): _serverAddress("127.0.0.1"), _serverPort("2244"), _serverSyncPort("2245")
    {
        _protocol = new Protocol_v1();
    };
    ~Communication() {};

    bool sendSpriteMovement(unsigned int pid, unsigned int x, unsigned int y);
    bool sendSpriteBombPlant(unsigned int pid, unsigned int x, unsigned int y);

    bool sendServerData();
    bool receiveServerData();

private:
    string _serverAddress;
    string _serverPort;
    string _serverSyncPort;
    vector<unsigned char> _bufferSend;
    TServerSync _dataReceive;
    Protocol_v1 *_protocol;

    unsigned int createBinaryData(unsigned int playerID, SEND_PACKET_TYPES type, 
        unsigned int locationX, unsigned int locationY);

    void errorSend();
    void errorSendPacketLength();
};

#endif