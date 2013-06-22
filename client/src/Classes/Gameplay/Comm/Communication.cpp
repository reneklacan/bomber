/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Communication
 */

#include "Communication.h"
#include "Sockets.h"

Communication *Communication::_instance = NULL;

Communication *Communication::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new Communication();
    }
    return _instance;
}

Communication::Communication()
:_serverAddress("127.0.0.1")
,_serverPort("2244")
{
    _protocol = new Protocol_v1();
};

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
    TcpClient tcpClient = TcpClient();
    std::vector<unsigned char> *data = tcpClient.receiveData(_serverAddress, _serverPort);
    _protocol->getDataServerSync(&_dataReceive, data);

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

//
PlayerInfo *Communication::getPlayerInfo(unsigned int pid)
{
    PlayerInfo *p = new PlayerInfo();
    p->valid = false;
    for(std::vector<TServerPlayer>::iterator it = _dataReceive.players_data.begin(); 
        it!= _dataReceive.players_data.end(); it++)
    {
        if(it->player_id == pid)
        {
            p->x = it->location_x;
            p->y = it->location_y;
            p->valid = true;
        }
    }
}
