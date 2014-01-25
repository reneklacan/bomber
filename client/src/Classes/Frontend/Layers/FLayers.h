#ifndef __BOMBER_FRONTEND_LAYERS_LAYER
#define __BOMBER_FRONTEND_LAYERS_LAYER

#include "cocos2d.h"

#include "../Statistics/FStatistics.h"
#include "ButtonLayer.h"
#include "../Buttons/ControlButton.h"
#include "../Primitives/Shapes.h"

#include <vector>

using namespace cocos2d;

namespace Bomber
{

    namespace Frontend
    {
        class Layers
        {
        public:
            Layer *getFinishLevelLayer(Statistics *statistics, std::vector<ccMenuCallback> callbacks);
            void createControlButtonLayer(std::vector<SEL_MenuHandler> callbacks, Layer* layer);
        };
    }
}

#endif