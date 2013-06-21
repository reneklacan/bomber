#ifndef __MAIN_MENU_LAYER
#define __MAIN_MENU_LAYER

#include "cocos2d.h"

using namespace cocos2d;

class MainMenuLayer : public CCLayer
{
    public:
        CREATE_FUNC(MainMenuLayer);

        MainMenuLayer();
        ~MainMenuLayer();
        static CCScene* scene();
        virtual bool init();
        void registerWithTouchDispatcher();

    private:
        void newGame(CCObject *sender);
};

#endif

