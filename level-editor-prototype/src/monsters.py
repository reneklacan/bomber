
from components import file_paths, textures

class EnemyPlayer:
    name = "Enemy Player"
    shortcut = "EP"
    register = True
    size_ratio = 0.5
    cls_texture = textures.player2_up

class PurpleFluffy:
    name = "Purple Fluffy"
    shortcut = "PF"
    register = True
    size_ratio = 0.8
    cls_texture = textures.purple_fluffy

class DummyGhost:
    name = "Dummy Ghost"
    shortcut = "DG"
    register = True
    size_ratio = 0.8
    cls_texture = textures.ghost

class FertileGhost:
    name = "Fertile Dummy Ghost"
    shortcut = "FDG"
    register = True
    size_ratio = 0.8
    cls_texture = textures.ghost

registered = (
        EnemyPlayer,
        PurpleFluffy,
        DummyGhost,
        FertileGhost,
)
