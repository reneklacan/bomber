/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: LocalServer
 */

#ifndef __BOMBER_LOCALSERVER_LAYER
#define __BOMBER_LOCALSERVER_LAYER

#include "Logic.h" 
#include "Sender.h"

/*
 * LocalServer is a Singleton object
 */
class LocalServer
{
public:
    // Singleton
    static LocalServer& getInstance();

    // Thread manipulation
    bool startServer();
    Logic *getLogic();
    Sender *getSender();
    bool endServer();

private:
    // Singleton
    LocalServer() {};
    LocalServer(LocalServer const&);
    void operator=(LocalServer const&);

    // Thread
    pthread_t _logicThread;
    pthread_t _senderThread;

    // Game Logic
    Logic *_logic;
    Sender *_sender;
};


#endif