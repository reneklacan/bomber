
#include "XMLStorage.h"

using namespace Bomber::Common;

XMLStorage *XMLStorage::_instance = nullptr;

XMLStorage *XMLStorage::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new XMLStorage();
    }
    return _instance;
}

XMLStorage::XMLStorage()
{
    _userDefaultInstance = cocos2d::UserDefault::sharedUserDefault();
}

void XMLStorage::set(std::string key, std::string value)
{
    this->set(key.c_str(), value);
}

void XMLStorage::set(char *key, std::string value)
{
    _userDefaultInstance->setStringForKey(key, value);
}

std::string XMLStorage::get(std::string key)
{
    return this->get(key.c_str());
}

std::string XMLStorage::get(char *key)
{
    return _userDefaultInstance->getStringForKey(key);
}

void XMLStorage::save()
{
    _userDefaultInstance->flush();
}
