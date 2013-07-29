#ifndef __BOMBER_BACKEND_CACHE
#define __BOMBER_BACKEND_CACHE

#include <map>
#include <deque>
#include <set>

#include "CachableObject.h"
#include "GameObjects\Effect.h"
#include "GameObjects\BBomb.h"
#include "GameObjects\Portal.h"
#include "GameObjects\PortalExit.h"

namespace Bomber
{
    namespace Backend
    {
        class BackendCache
        {
            public:
                Effect *getEffect();
                void returnEffect(Effect *object);
                Bomb *getBomb();
                void returnBomb(Bomb *bomb);

                static BackendCache* getInstance();

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