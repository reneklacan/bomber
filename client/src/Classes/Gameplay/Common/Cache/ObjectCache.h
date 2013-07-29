#ifndef __BOMBER_COMMON_OBJECT_CACHE
#define __BOMBER_COMMON_OBJECT_CACHE

#include <map>
#include <deque>
#include <set>

#include "CachableObject.h"

namespace Bomber
{
    namespace Common
    {
        class ObjectCache
        {
            public:
                static ObjectCache* getInstance();
                
                void enable() { _enabled = true; };
                void disable() { _enabled = false; };
                CachableObject* getObject(TCachableObjectType type);
                void returnObject(CachableObject *object);
                void reset(TCachableObjectType type);
                void reset();
                void free(TCachableObjectType type);
                void free();

            private:
                static ObjectCache* _instance;

                ObjectCache();

                bool _enabled;
                std::map<TCachableObjectType, std::deque<CachableObject *> > _freeInstances;
                std::map<TCachableObjectType, std::set<CachableObject *> > _occupiedInstances;
        };
    }
}

#endif