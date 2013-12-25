#ifndef __BOMBER_COMMON_XML_STORAGE
#define __BOMBER_COMMON_XML_STORAGE

#include "cocos2d.h"

namespace Bomber
{
    namespace Common
    {
        class XMLStorage
        {
            public:
                static XMLStorage *getInstance();

                void set(std::string key, std::string value);
                void set(char *key, std::string value);
                void set(std::string prefix, std::string key, std::string value);
                std::string get(std::string key);
                std::string get(char *key);
                std::string get(std::string prefix, std::string key);
                std::string getLevelStatus(std::string key);
                std::string getPath(); // segfault? :(
                void save();

            private:
                static XMLStorage *_instance;
                cocos2d::UserDefault *_userDefaultInstance;

                XMLStorage();
        };
    }
}

#endif
