#ifndef __LEVEL_SELECT_LAYER
#define __LEVEL_SELECT_LAYER

#include "cocos2d.h"

#include "../Frontend/Primitives/MenuHelper.h"
#include "PlayersSelectLayer.h"

#include <sys/types.h>
#include <string>

using namespace cocos2d;

class LevelSelectLayer : public Layer
{
    public:

        CREATE_FUNC(LevelSelectLayer);

        LevelSelectLayer(){}
        ~LevelSelectLayer(){}

        static Scene* scene();
        virtual bool init();
        void registerWithTouchDispatcher();

    private:

        void playersSelect(Object *sender, std::string levelName);
};

#endif