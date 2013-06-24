#ifndef __BOMBER_GAME_OBJECT_EVENT_DELEGATE
#define __BOMBER_GAME_OBJECT_EVENT_DELEGATE

class GameStateChange;

class GameObjectEventDelegate
{
    virtual void update(GameStateChange *change) = 0;
};

#endif
