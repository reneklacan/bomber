
#include "ReceiveDelegator.h"

void ReceiveDelegator::addReceiveDelegate(ReceiveDelegate *delegate)
{
    _receiveDelegates.insert(delegate);
}

void ReceiveDelegator::delegateReceivedMessage(const char *msg)
{
    for (ReceiveDelegate *delegate : _receiveDelegates)
    {
        delegate->receiveData(msg);
    }
}
