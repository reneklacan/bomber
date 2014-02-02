#ifndef __BOMBER_FRONTEND_BUBBLE
#define __BOMBER_FRONTEND_BUBBLE

#include "cocos2d.h"
#include "GameButton.h"
#include "../Primitives/Shapes.h"
#include "../GUIConstants.h"

#include <string>

namespace Bomber
{
    namespace Frontend
    {
        class Bubble : public GameButton
        {
        public:
            Bubble(std::string title, std::string description, std::string image);
        };
    }
}

#endif