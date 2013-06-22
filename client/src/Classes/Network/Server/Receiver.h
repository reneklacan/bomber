#ifndef __BOMBER_RECEIVER
#define __BOMBER_RECEIVER

#include <boost/shared_ptr.hpp>

#include "../Common/Message.h"

class Receiver
{
    public:
        virtual ~Receiver() {};
        virtual void dispatch(const Message& msg) = 0;
};

typedef boost::shared_ptr<Receiver> ReceiverSPtr;

#endif

