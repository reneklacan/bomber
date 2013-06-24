#ifndef __BOMBER_GAME_STATE_CHANGE
#define __BOMBER_GAME_STATE_CHANGE

#include "GameObject.h"

enum TGameStateChangeType
{
    SPRITE_MOVE,
    SPRITE_POSITION_OVERRIDE,
    SPRITE_SPAWN,
    SPRITE_DESTROY,
    SPRITE_UPDATE,

    OBSTACLE_DESTROY,
    OBSTACLE_SPAWN,

    BOMB_SPAWN,

    EXPLOSION_SPAWN,
    EXPLOSION_DESTROY,

    SPECIAL_SPAWN,
    SPECIAL_DESTROY
};

class GameStateChange
{
    public:
        GameStateChange();

        GameObject *getGameObject() { return _object; };

    private:
        int _type;
        GameObject* _object;
};

#endif
