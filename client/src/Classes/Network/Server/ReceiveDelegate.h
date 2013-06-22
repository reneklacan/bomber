#ifndef __BOMBER_RECEIVE_DELEGATE
#define __BOMBER_RECEIVE_DELEGATE

class ReceiveDelegate
{
    public:
        virtual void receiveServerData(const char *) = 0;
};

#endif
