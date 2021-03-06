#ifndef __BOMBER_GAME_STATE_CHANGE
#define __BOMBER_GAME_STATE_CHANGE

#include "../../Macros.h"
#include "../Primitives/Position.h"
#include "../Primitives/Coordinates.h"

namespace Bomber
{
    namespace Common
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
            BOMB_MOVE,

            EXPLOSION_SPAWN,
            EXPLOSION_DESTROY,

            EFFECT_SPAWN,
            EFFECT_DESTROY,

            SPECIAL_SPAWN,
            SPECIAL_DESTROY,

            ACHIEVEMENT_UNLOCKED,
            
            BLOCK_PUSH,

            LEVER_SWITCH_ON,
            LEVER_SWITCH_OFF,

            DIALOG_BUBBLE,

            FOG_ON,
            FOG_OFF,

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
                virtual void update(Common::Position p) { _position = p; };

            private:
                SYNTHESIZE(Common::Position, _position, Position);
        };

        class GSCCoordinates : public GameStateChange
        {
            public:
                virtual void update(Common::Coordinates coords) { _coordinates = coords; };

            private:
                SYNTHESIZE(Common::Coordinates, _coordinates, Coordinates);
        };

        class GSCSpriteMove : public GSCPosition
        {
            public:
                GSCSpriteMove() { _type = SPRITE_MOVE; };
        };

        class GSCBombMove : public GSCPosition
        {
            public:
                GSCBombMove() { _type = BOMB_MOVE; };
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
                virtual void update(unsigned int gid, Common::Coordinates coords)
                {
                    _gid = gid;
                    _coordinates = coords;
                }

            private:
                SYNTHESIZE(unsigned int, _gid, Gid);
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
                virtual void update(unsigned int gid, Common::Coordinates coords, unsigned int spawnerId)
                {
                    _gid = gid;
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
                virtual void update(unsigned int owner, Common::Position epicentrum, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength)
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
                SYNTHESIZE(Common::Position, _epicentrum, Epicentrum);
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
                virtual void update(unsigned int gid, int type)
                {
                    _gid = gid;
                    _effectType = type;
                }

            private:
                SYNTHESIZE(unsigned int, _gid, Gid);
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

        class GSCBlockPush : public GameStateChange
        {
            public:
                GSCBlockPush() { _type = BLOCK_PUSH; };
                virtual void update(Common::Coordinates from, Common::Coordinates to)
                {
                    _from = from;
                    _to = to;
                }
                
            private:
                SYNTHESIZE(Common::Coordinates, _from, From);
                SYNTHESIZE(Common::Coordinates, _to, To);
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
                virtual void update(unsigned int bombSpawns, unsigned int totalKills, 
                                    unsigned int totalEffects, unsigned int totalObstacles, 
                                    unsigned int teleportUses, unsigned int leverUses)
                {
                    _bombSpawns = bombSpawns;
                    _totalKills = totalKills;
                    _totalEffects = totalEffects;
                    _totalObstacles = totalObstacles;
                    _teleportUses = teleportUses;
                    _leverUses = leverUses;
                }
            private:
                SYNTHESIZE(unsigned int, _bombSpawns, BombSpawns);
                SYNTHESIZE(unsigned int, _totalKills, TotalKills);
                SYNTHESIZE(unsigned int, _totalEffects, TotalEffects);
                SYNTHESIZE(unsigned int, _totalObstacles, TotalObstacles);
                SYNTHESIZE(unsigned int, _teleportUses, TeleportUses);
                SYNTHESIZE(unsigned int, _leverUses, LeverUses);
        };

        class GSCLevelReset : public GameStateChange
        {
            public:
                GSCLevelReset() { _type = LEVEL_RESET; };
        };

        class GSCDialogBubble : public GameStateChange
        {
            public:
                GSCDialogBubble() { _type = DIALOG_BUBBLE; };
                virtual void update(const char *title, const char *description, const char* image)
                {
                    _title = title;
                    _description = description;
                    _image = image;
                }

            private:
                SYNTHESIZE(const char *, _title, Title);
                SYNTHESIZE(const char *, _description, Description);
                SYNTHESIZE(const char *, _image, Image);
        };

        class GSCFogOn : public GameStateChange
        {
            public:
                GSCFogOn() { _type = FOG_ON; };
        };

        class GSCFogOff : public GameStateChange
        {
            public:
                GSCFogOff() { _type = FOG_OFF; };
        };
    }
}

#endif
