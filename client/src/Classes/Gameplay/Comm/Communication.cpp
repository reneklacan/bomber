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
    if( createBinaryData(pid, MOVE, x, y) != SEND_PAKET_LENGTH )
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
    if( createBinaryData(pid, PLANT, x, y) != SEND_PAKET_LENGTH )
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
    SEND_PACKET_TYPES type, unsigned int location_x, unsigned int location_y)
{
    unsigned int sessionID = 14568; // TODO

    // Set Session ID
    _bufferSend.push_back( (unsigned char)(sessionID / 256) );
    _bufferSend.push_back( (unsigned char)(sessionID % 256) );
    // Set Player ID
    _bufferSend.push_back( (unsigned char)(playerID / 256) );
    _bufferSend.push_back( (unsigned char)(playerID % 256) );
    // Set Type of Data
    _bufferSend.push_back( (unsigned char)type );
    // Set Location X
    _bufferSend.push_back( (unsigned char)(location_x / 256) );
    _bufferSend.push_back( (unsigned char)(location_x % 256) );
    // Set Location Y
    _bufferSend.push_back( (unsigned char)(location_y / 256) );
    _bufferSend.push_back( (unsigned char)(location_y % 256) );

    return SEND_PAKET_LENGTH;
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