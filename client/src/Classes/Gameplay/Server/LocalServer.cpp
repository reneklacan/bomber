/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: LocalServer
 */

#include "LocalServer.h"

// Clean function to start thread
void *logicHelper(void * arg)
{
    LocalServer::getInstance().getLogic()->init();
}

// Singleton
LocalServer& LocalServer::getInstance()
{
    static LocalServer _localServer;
    return _localServer;
}

// Create new thread for Logic and Sender and call initialization method
bool LocalServer::startServer()
{
    _logic = new Logic();
    pthread_create(&_logicThread, NULL, logicHelper, NULL);

    return true;
}

// Return pointer to Logic class
Logic *LocalServer::getLogic()
{
    return _logic;
}

// TODO: implement
bool LocalServer::endServer()
{
    return false;
}