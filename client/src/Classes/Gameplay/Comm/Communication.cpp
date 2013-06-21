/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Communication
 */

#include "Communication.h"
#include "Sockets.h"


//
bool Communication::sendSpriteMovement(unsigned int pid, unsigned int x, unsigned int y) 
{
    if( createBinaryData(pid, MOVE, x, y) != PLAYER_ACTION_PAKET_LENGTH )
    {
    	errorSendPacketLength();
    }

    if( !sendServerData() )
    {
    	errorSend();
    }

    return true;
}

//
bool Communication::sendSpriteBombPlant(unsigned int pid, unsigned int x, unsigned int y)
{
    if( createBinaryData(pid, PLANT, x, y) != PLAYER_ACTION_PAKET_LENGTH )
    {
    	errorSendPacketLength();
    }

    if( !sendServerData() )
    {
    	errorSend();
    }


    return true;
}

//
unsigned int Communication::createBinaryData(unsigned int playerID, 
    SEND_PACKET_TYPES type, unsigned int locationX, unsigned int locationY)
{
    TPlayerAction data = 
    {
        type,
        14568,  //TODO
        playerID, 
        locationX,
        locationY,
    };

    _protocol->setDataPlayerAction(_bufferSend, &data);

    return _bufferSend.size();
}

//
bool Communication::sendServerData()
{
    TcpClient tcpClient = TcpClient();
    tcpClient.sendData(_serverAddress, _serverPort, _bufferSend);
    _bufferSend.clear();

    return true;
}

//
bool Communication::receiveServerData()
{
    return true;
}

//
void Communication::errorSend()
{
    cerr << "Could not send data to a server." << endl;
}

//
void Communication::errorSendPacketLength()
{
    cerr << "Wrong length of created packet." << endl;
}