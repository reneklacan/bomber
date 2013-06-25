#ifndef __BOMBER_RECEIVE_DELEGATOR
#define __BOMBER_RECEIVE_DELEGATOR

#include <set>

#include "ReceiveDelegate.h"

class ReceiveDelegator
{
    public:
        virtual void addReceiveDelegate(ReceiveDelegate *delegate);
        virtual void delegateReceivedMessage(const char *msg);

    protected:
        std::set<ReceiveDelegate *> _receiveDelegates;
};

#endif

