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
#include "../../Network/Client/ClientConnection.h"

using namespace std;

class PlayerInfo
{
public:
    PlayerInfo() {}
    ~PlayerInfo() {}

    unsigned int x;
    unsigned int y;
    bool valid;
};

class Communication
{
    public:
        ~Communication() {};

        static Communication *getInstance();

        bool sendSpriteMovement(unsigned int pid, unsigned int x, unsigned int y);
        bool sendSpriteBombPlant(unsigned int pid, unsigned int x, unsigned int y);

        bool sendServerData();
        bool receiveServerData();

        PlayerInfo *getPlayerInfo(unsigned int pid);

    private:
        static Communication *_instance;

        string _serverAddress;
        string _serverPort;
        vector<unsigned char> _bufferSend;
        TServerSync _dataReceive;
        Protocol_v1 *_protocol;
        ClientConnection *_clientConnection;

        Communication();
        unsigned int createBinaryData(unsigned int playerID, SEND_PACKET_TYPES type, 
                unsigned int locationX, unsigned int locationY);

        void errorSend();
        void errorSendPacketLength();
};

#endif
