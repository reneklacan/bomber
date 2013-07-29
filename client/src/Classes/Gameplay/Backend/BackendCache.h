#ifndef __BOMBER_BACKEND_CACHE
#define __BOMBER_BACKEND_CACHE

#include <map>
#include <deque>
#include <set>

#include "CachableObject.h"

namespace Bomber
{
    namespace Backend
    {
        class BackendCache
        {
            public:
                static BackendCache* getInstance();
                
                void enable() { _enabled = true; };
                void disable() { _enabled = false; };
                CachableObject* getObject(TCachableObjectType type);
                void returnObject(CachableObject *object);
                void reset(TCachableObjectType type);
                void reset();

            private:
                static BackendCache* _instance;

                BackendCache();

                bool _enabled;
                std::map<TCachableObjectType, std::deque<CachableObject *> > _freeInstances;
                std::map<TCachableObjectType, std::set<CachableObject *> > _occupiedInstances;
        };
    }
}

#endif