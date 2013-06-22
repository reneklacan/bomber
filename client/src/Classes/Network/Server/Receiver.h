#ifndef __BOMBER_RECEIVER
#define __BOMBER_RECEIVER

#include <boost/shared_ptr.hpp>

#include "../Common/ReceiveDelegator.h"
#include "../Common/Message.h"

class Receiver : public ReceiveDelegator
{
    public:
        virtual ~Receiver() {};
        virtual void dispatch(const Message& msg) = 0;
};

typedef boost::shared_ptr<Receiver> ReceiverSPtr;

#endif

