
from components import file_paths, textures

class MonsterBase:
    def __repr__(cls):
        return cls.shortcut

    def __str__(cls):
        return cls.shortcut

class EnemyPlayer(MonsterBase):
    name = "Enemy Player"
    shortcut = "EP"
    cls_texture = textures.player2_up

class PurpleFluffy(MonsterBase):
    name = "Purple Fluffy"
    shortcut = "PF"
    cls_texture = textures.purple_fluffy

class DummyGhost(MonsterBase):
    name = "Dummy Ghost"
    shortcut = "DG"
    cls_texture = textures.ghost

class FertileGhost(MonsterBase):
    name = "Fertile Dummy Ghost"
    shortcut = "FDG"
    cls_texture = textures.ghost

registered = (
        EnemyPlayer,
        PurpleFluffy,
        DummyGhost,
        FertileGhost,
)
