#ifndef __BOMBER_MESSAGE
#define __BOMBER_MESSAGE

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>


class Message
{
    public:
        enum { headerLength = 4 };
        enum { maxBodyLength = 512 };

        Message();

        const char* data() const;
        char* data();
        size_t length() const;
        const char* body() const;
        char* body();
        size_t bodyLength() const;
        void bodyLength(size_t length);
        bool decodeHeader();
        void encodeHeader();

    private:
        char _data[headerLength + maxBodyLength];
        size_t _bodyLength;

        //static int headerLength;
        //static int maxBodyLength;
};

//int Message::headerLength = 4;
//int Message::maxBodyLength = 512;

typedef std::deque<Message> MessageQueue;

#endif

