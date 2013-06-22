
#include "Message.h"

Message::Message()
:_bodyLength(0)
{
}

const char* Message::data() const
{
    return _data;
}

char* Message::data()
{
    return _data;
}

size_t Message::length() const
{
    return headerLength + _bodyLength;
}

const char* Message::body() const
{
    return _data + headerLength;
}

char* Message::body()
{
    return _data + headerLength;
}

size_t Message::bodyLength() const
{
    return _bodyLength;
}

void Message::bodyLength(size_t length)
{
    _bodyLength = length;
    if (_bodyLength > maxBodyLength)
    {
        _bodyLength = maxBodyLength;
    }
}

bool Message::decodeHeader()
{
    char header[headerLength + 1] = "";
    std::strncat(header, _data, headerLength);
    _bodyLength = std::atoi(header);
    if (_bodyLength > maxBodyLength)
    {
        _bodyLength = 0;
        return false;
    }
    return true;
}

void Message::encodeHeader()
{
    char header[headerLength + 1] = "";
    std::sprintf(header, "%4d", (int) _bodyLength);
    std::memcpy(_data, header, headerLength);
}
