#ifndef __BOMBER_FRONTEND_PRIM_PATH
#define __BOMBER_FRONTEND_PRIM_PATH

#include "cocos2d.h"

using namespace cocos2d;

namespace Bomber
{
    namespace Frontend
    {
        class Path
        {
        public:
            Path(unsigned int from, unsigned int to, Sprite* sprite)
            : _oldId(from), _newId(to), _sprite(sprite) 
            {}

            void setFrom(unsigned int from) { _oldId = from; }
            void setTo(unsigned int from) { _newId = from; }
            void setSprite(Sprite* sprite) { _sprite = sprite; }
            unsigned int getFrom() { return _oldId; }
            unsigned int getTo() { return _newId; }
            Sprite* getSprite() { return _sprite; }
            
        private:
            unsigned int _oldId;
            unsigned int _newId;
            Sprite* _sprite;
        };
    }
}

#endif