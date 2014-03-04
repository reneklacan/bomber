#ifndef __BOMBER_BACKEND_TEXT
#define __BOMBER_BACKEND_TEXT

#include "GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class Text : public GameObject
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_TEXT; };

            private:
                SYNTHESIZE(char *, _title, Title);
                SYNTHESIZE(char *, _text, Text);
                SYNTHESIZE(time_t, _lastDisplayAt, LastDisplayAt);
                SYNTHESIZE(float, _timeout, Timeout);
        };
    }
}

#endif
