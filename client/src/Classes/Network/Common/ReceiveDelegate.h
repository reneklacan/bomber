#ifndef __BOMBER_RECEIVE_DELEGATE
#define __BOMBER_RECEIVE_DELEGATE

class ReceiveDelegate
{
    public:
        virtual void receiveData(const char *) = 0;
};

#endif

