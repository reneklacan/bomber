#ifndef __BOMBER_RECEIVER_CONTAINER
#define __BOMBER_RECEIVER_CONTAINER

#include <set>

#include "Receiver.h"

class ReceiverContainer
{
    public:
        void add(ReceiverSPtr receiver);
        void remove(ReceiverSPtr receiver);
        void dispatch(const Message& msg);

    private:
        std::set<ReceiverSPtr> _receivers;
};

#endif

