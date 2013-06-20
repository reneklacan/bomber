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

using namespace std;

#define SEND_PAKET_LENGTH 9 // number of Bytes

// Types of packets for sending to a server
enum SEND_PACKET_TYPES {
    MOVE,
    PLANT
};

class Communication {
public:
    Communication(): _serverAddress("127.0.0.1"), _serverPort("2244") {};
    ~Communication() {};

    bool sendSpriteMovement(unsigned int pid, unsigned int x, unsigned int y);
    bool sendSpriteBombPlant(unsigned int pid, unsigned int x, unsigned int y);

    bool sendServerData();
    bool receiveServerData();

private:
    string _serverAddress;
    string _serverPort;
    vector<unsigned char> _bufferSend;
    vector<unsigned char> _bufferReceive;

    unsigned int createBinaryData(unsigned int playerID, SEND_PACKET_TYPES type, 
        unsigned int location_x, unsigned int location_y);

    void errorSend();
    void errorSendPacketLength();
};

#endif