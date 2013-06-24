#ifndef __BOMBER_GAME_STATE
#define __BOMBER_GAME_STATE

#include "GameStateLayer.h"
#include "GameStateChange.h"

class GameState
{
    public:
        GameState();
        ~GameState();

    private:
        std::vector<GameStateChange *> _changes;

        GameStateLayer *_sprites;
        GameStateLayer *_obstacles;
        GameStateLayer *_portals;
        GameStateLayer *_specials;
        GameStateLayer *_bombs;
};

#endif
