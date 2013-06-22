#ifndef __BOMBER_RECEIVER_CONTAINER
#define __BOMBER_RECEIVER_CONTAINER

#include <set>

#include "ReceiveDelegate.h"
#include "Receiver.h"

class ReceiverContainer
{
    public:
        void add(ReceiverSPtr receiver);
        void remove(ReceiverSPtr receiver);
        void dispatch(const Message& msg);
        std::set<ReceiverSPtr>& getAll() { return _receivers; };
        void addReceiveDelegate(ReceiveDelegate *delegate);

    private:
        std::set<ReceiverSPtr> _receivers;
        std::set<ReceiveDelegate *> _receiveDelegates;
};

#endif

