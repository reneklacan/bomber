#ifndef __BOMBER_GAME_STATE_CHANGE
#define __BOMBER_GAME_STATE_CHANGE

#include "Macros.h"
#include "Primitives/Position.h"

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
            SPRITE_DAMAGE,
            SPRITE_DESTROY,
            SPRITE_ATTR_UPDATE,

            OBSTACLE_DESTROY,
            OBSTACLE_SPAWN,

            BOMB_SPAWN,
            BOMB_DESTROY,

            EXPLOSION_SPAWN,
            EXPLOSION_DESTROY,

            EFFECT_SPAWN,
            EFFECT_DESTROY,

            SPECIAL_SPAWN,
            SPECIAL_DESTROY,

            ACHIEVEMENT_UNLOCKED,
            
            LEVER_SWITCH_ON,
            LEVER_SWITCH_OFF,

            LEVEL_FINISH
        };

        class GameStateChange
        {
            public:
                GameStateChange() { _type = NONE; };

            protected:
                SYNTHESIZE(TGameStateChangeType, _type, Type);
                SYNTHESIZE(unsigned int, _gameObjectId, GameObjectId);
        };

        class GSCPosition : public GameStateChange
        {
            public:
                virtual void update(Position p) { _position = p; };

            private:
                SYNTHESIZE(Position, _position, Position);
        };

        class GSCCoordinates : public GameStateChange
        {
            public:
                virtual void update(Coordinates c) { _coordinates = c; };

            private:
                SYNTHESIZE(Coordinates, _coordinates, Coordinates);
        };

        class GSCSpriteMove : public GSCPosition
        {
            public:
                GSCSpriteMove() { _type = SPRITE_MOVE; };
        };

        class GSCSpriteTeleport : public GSCPosition
        {
            public:
                GSCSpriteTeleport() { _type = SPRITE_TELEPORT; };
        };

        class GSCSpriteDamage : public GameStateChange
        {
            public:
                GSCSpriteDamage() { _type = SPRITE_DAMAGE; };
                virtual void update(int damage) { _damage = damage; };

            private:
                SYNTHESIZE(int, _damage, Damage);
        };

        class GSCSpriteDestroy : public GameStateChange
        {
            public:
                GSCSpriteDestroy() { _type = SPRITE_DESTROY; };
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
                SYNTHESIZE(unsigned int, _id, Id);
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
                virtual void update(unsigned int owner, Position epicentrum, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength)
                {
                    _owner = owner;
                    _epicentrum = epicentrum;
                    _topArmLength = topArmLength;
                    _bottomArmLength = bottomArmLength;
                    _leftArmLength = leftArmLength;
                    _rightArmLength = rightArmLength;
                };
            private:
                SYNTHESIZE(unsigned int, _owner, Owner);
                SYNTHESIZE(Position, _epicentrum, Epicentrum);
                SYNTHESIZE(unsigned int, _topArmLength, TopArmLength);
                SYNTHESIZE(unsigned int, _bottomArmLength, BottomArmLength);
                SYNTHESIZE(unsigned int, _leftArmLength, LeftArmLength);
                SYNTHESIZE(unsigned int, _rightArmLength, RightArmLength);
        };

        class GSCEffectDestroy : public GSCCoordinates
        {
            public:
                GSCEffectDestroy() { _type = EFFECT_DESTROY; };
        };

        class GSCSpriteAttrUpdate : public GameStateChange
        {
            public:
                GSCSpriteAttrUpdate() { _type = SPRITE_ATTR_UPDATE; };
                virtual void update(int type) { _effectType = type; };

            private:
                SYNTHESIZE(int, _effectType, EffectType);
        };

        class GSCAchievementUnlocked : public GameStateChange
        {
            public:
                GSCAchievementUnlocked() { _type = ACHIEVEMENT_UNLOCKED; };
                virtual void update(const char *title, const char *description)
                {
                    _title = title;
                    _description = description;
                }

            private:
                SYNTHESIZE(const char *, _title, Title);
                SYNTHESIZE(const char *, _description, Description);
        };
    }
}

#endif
