#ifndef __MAIN_MENU_LAYER
#define __MAIN_MENU_LAYER

#include "cocos2d.h"

using namespace cocos2d;

class MainMenuLayer : public Layer
{
    public:
        CREATE_FUNC(MainMenuLayer);

        MainMenuLayer();
        ~MainMenuLayer();
        static Scene* scene();
        virtual bool init();
        void registerWithTouchDispatcher();

    private:
        void newGame(Object *sender);
        void showLevels(Object *sender);
};

#endif

