
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
    _userDefaultInstance->setStringForKey(key.c_str(), value);
}

void XMLStorage::set(char *key, std::string value)
{
    _userDefaultInstance->setStringForKey(key, value);
}

void XMLStorage::set(std::string prefix, std::string key, std::string value)
{
    std::string keyWithPrefix = prefix + "_" + key;
    this->set(keyWithPrefix, value);
}

std::string XMLStorage::get(std::string key)
{
    return _userDefaultInstance->getStringForKey(key.c_str());
}

std::string XMLStorage::get(char *key)
{
    return _userDefaultInstance->getStringForKey(key);
}

std::string XMLStorage::get(std::string prefix, std::string key)
{
    std::string keyWithPrefix = prefix + "_" + key;
    return this->get(keyWithPrefix);
}

std::string XMLStorage::getPath()
{
    _userDefaultInstance->getXMLFilePath();
}

void XMLStorage::save()
{
    _userDefaultInstance->flush();
}
