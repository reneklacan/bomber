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

            LEVEL_FINISH,
            LEVEL_RESET,
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
                virtual void update(Coordinates coords) { _coordinates = coords; };

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

        class GSCGidOnCoordinates : public GSCCoordinates
        {
            public:
                GSCGidOnCoordinates() { _type = NONE; };
                virtual void update(unsigned int gid, Coordinates coords)
                {
                    _git = gid;
                    _coordinates = coords;
                }

            private:
                SYNTHESIZE(unsigned int, _git, Gid);
        };

        class GSCSpriteSpawn : public GSCGidOnCoordinates
        {
            public:
                GSCSpriteSpawn() { _type = SPRITE_SPAWN; };
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
        
        class GSCObstacleSpawn : public GSCGidOnCoordinates
        {
            public:
                GSCObstacleSpawn() { _type = OBSTACLE_SPAWN; };
                virtual void update(unsigned int gid, Coordinates coords, unsigned int spawnerId)
                {
                    _git = gid;
                    _coordinates = coords;
                    _spawnerId = spawnerId;
                }

            private:
                SYNTHESIZE(unsigned int, _spawnerId, SpawnerId);
        };
        
        class GSCEffectSpawn : public GSCGidOnCoordinates
        {
            public:
                GSCEffectSpawn() { _type = EFFECT_SPAWN; };
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

        class GSCLeverSwitchOn : public GameStateChange
        {
            public:
                GSCLeverSwitchOn() { _type = LEVER_SWITCH_ON; };
        };

        class GSCLeverSwitchOff : public GameStateChange
        {
            public:
                GSCLeverSwitchOff() { _type = LEVER_SWITCH_OFF; };
        };

        class GSCLevelFinish : public GameStateChange
        {
            public:
                GSCLevelFinish() { _type = LEVEL_FINISH; };
        };

        class GSCLevelReset : public GameStateChange
        {
            public:
                GSCLevelReset() { _type = LEVEL_RESET; };
        };
    }
}

#endif
