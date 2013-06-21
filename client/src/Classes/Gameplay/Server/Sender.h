/*
 * Project: Bomber
 * Created: 19.06.2013
 * Class: Sender
 */

#ifndef __BOMBER_SENDER_LAYER
#define __BOMBER_SENDER_LAYER

#include <iostream>
#include <vector>
#include "Logic.h"
#include "../Comm/Protocol_v1.h"
#include "../Comm/Sockets.h"

class Sender {
public:
    Sender();
    ~Sender() {}

    void init();
    void setLogic(Logic* logic);
private:
    Logic *_logic;
    Protocol_v1 *_protocol;
    std::vector<unsigned char> _buffer;
    TServerSync _data;
};

#endif