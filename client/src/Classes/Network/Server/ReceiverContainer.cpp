
#include <boost/bind.hpp>

#include "ReceiverContainer.h"

void ReceiverContainer::add(ReceiverSPtr receiver)
{
    _receivers.insert(receiver);

    for (ReceiveDelegate *delegate : _receiveDelegates)
    {
        receiver->addReceiveDelegate(delegate);
    }
}

void ReceiverContainer::remove(ReceiverSPtr receiver)
{
    _receivers.erase(receiver);
}

void ReceiverContainer::dispatch(const Message& msg)
{
    std::for_each(
            _receivers.begin(),
            _receivers.end(),
            boost::bind(
                &Receiver::dispatch,
                _1,
                boost::ref(msg)
            )
    );
}

void ReceiverContainer::addReceiveDelegate(ReceiveDelegate *delegate)
{
    _receiveDelegates.insert(delegate);
    std::for_each(
            _receivers.begin(),
            _receivers.end(),
            boost::bind(
                &Receiver::addReceiveDelegate,
                _1,
                boost::ref(delegate)
            )
    );
}
