
#include <boost/bind.hpp>

#include "ReceiverContainer.h"

void ReceiverContainer::add(ReceiverSPtr receiver)
{
    _receivers.insert(receiver);
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
