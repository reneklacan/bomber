#ifndef __BOMBER_GAME_STATE_CHANGE
#define __BOMBER_GAME_STATE_CHANGE

#include "Position.h"

namespace Bomber
{
    namespace Backend
    {
        enum TGameStateChangeType
        {
            NONE,

            SPRITE_MOVE,
            SPRITE_TELEPORT,
            SPRITE_SPAWN,
            SPRITE_DESTROY,
            SPRITE_UPDATE,

            OBSTACLE_DESTROY,
            OBSTACLE_SPAWN,

            BOMB_SPAWN,
            BOMB_DESTROY,

            EXPLOSION_SPAWN,
            EXPLOSION_DESTROY,

            SPECIAL_SPAWN,
            SPECIAL_DESTROY
        };

        class GameStateChange
        {
            public:
                GameStateChange() { _type = NONE; };

                void setGameObjectId(unsigned int id) { _gameObjectId = id; };
                unsigned int getGameObjectId() { return _gameObjectId; };
                TGameStateChangeType getType() { return _type; };

            protected:
                TGameStateChangeType _type;
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

        class GSCSpriteTeleport : public GSCPosition
        {
            public:
                GSCSpriteTeleport() { _type = SPRITE_TELEPORT; };
        };

        class GSCBombSpawn : public GSCPosition
        {
            public:
                GSCBombSpawn() { _type = BOMB_SPAWN; };
        };

        class GSCBombDestroy : public GameStateChange
        {
            public:
                GSCBombDestroy() { _type = BOMB_DESTROY; };
                virtual void update(unsigned int id) { _id = id; };
            private:
                unsigned int _id;
        };

        class GSCObstacleDestroy : public GSCCoordinates
        {
            public:
                GSCObstacleDestroy() { _type = OBSTACLE_DESTROY; };
        };

        class GSCExplosionSpawn : public GameStateChange
        {
            public:
                GSCExplosionSpawn() { _type = EXPLOSION_SPAWN; };
                virtual void update(unsigned int owner, unsigned int power, unsigned int penetration)
                {
                    _owner = owner; _power = power; _penetration = penetration;
                };
            private:
                unsigned int _owner;
                int _power;
                int _penetration;
        };
    }
}

#endif
