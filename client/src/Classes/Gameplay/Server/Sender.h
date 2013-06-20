/*
 * Project: Bomber
 * Created: 19.06.2013
 * Class: Sender
 */

#ifndef __BOMBER_SENDER_LAYER
#define __BOMBER_SENDER_LAYER

#include <iostream>
#include "Logic.h"

class Sender {
public:
    Sender() {};
    ~Sender() {};

    void init();
    void setLogic(Logic* logic);
private:
    Logic *_logic;
};

#endif