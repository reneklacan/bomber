#ifndef __PLAYERS_SELECT_LAYER
#define __PLAYERS_SELECT_LAYER

#include "cocos2d.h"

#include "../GameplayScene.h"
#include "../Frontend/Primitives/MenuHelper.h"

#include <sys/types.h>
#include <string>

using namespace cocos2d;

class PlayersSelectLayer : public Layer
{
    public:

        CREATE_FUNC(PlayersSelectLayer);

        PlayersSelectLayer(){}
        ~PlayersSelectLayer(){}

        static Scene* scene();
        virtual bool init();
        void registerWithTouchDispatcher();

    private:

        void newGame(Object *sender, unsigned int numPlayers);
};

#endif