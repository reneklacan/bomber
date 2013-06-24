#ifndef __BOMBER_GAME_STATE_CHANGE
#define __BOMBER_GAME_STATE_CHANGE

#include "Position.h"

namespace Bomber
{
    namespace Backend
    {
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
                GameStateChange() { _type = 0; };

                void setGameObjectId(unsigned int id) { _gameObjectId = id; };
                unsigned int getGameObjectId() { return _gameObjectId; };

            protected:
                int _type;
                unsigned int _gameObjectId;
        };

        class GSCPosition : public GameStateChange
        {
            public:
                virtual void update(Position p) { _position = p; };

            private:
                Position _position;
        };

        class GSCCoordinates : public GameStateChange
        {
            public:
                virtual void update(Coordinates c) { _coordinates = c; };

            private:
                Coordinates _coordinates;
        };

        class GSCSpriteMove : public GameStateChange
        {
            public:
                GSCSpriteMove() { _type = SPRITE_MOVE; };
                virtual void update(Position &p, Position &np) { _position = p; _nextPosition = np; };
            private:
                Position _position;
                Position _nextPosition;
        };

        class GSCSpritePositionOverride : public GSCPosition
        {
            public:
                GSCSpritePositionOverride() { _type = SPRITE_POSITION_OVERRIDE; };
        };

        class GSCBombSpawn : public GSCPosition
        {
            public:
                GSCBombSpawn() { _type = BOMB_SPAWN; };
        };

        class GSCObstacleDestroy : public GameStateChange
        {
            public:
                GSCObstacleDestroy() { _type = OBSTACLE_DESTROY; };
        };
    }
}

#endif
