
import time
import string
from kivy.core.window import Window
from kivy.core.image import Image
from kivy.graphics import Rectangle

res_dir = './'

class FilePathsMap:
    def __init__(self):
        self.space = res_dir + 'resources/images/map/space.gif'
        self.block = res_dir + 'resources/images/map/block.jpg'
        self.maze = res_dir + 'resources/images/map/maze.jpg'
        self.bomb = res_dir + 'resources/images/map/bomb.gif'

        self.flame_center = res_dir + 'resources/images/map/flame_center.gif'
        self.flame_v = res_dir + 'resources/images/map/flame_v.gif'
        self.flame_h = res_dir + 'resources/images/map/flame_h.gif'
        self.flame_end_top = res_dir + 'resources/images/map/flame_end_top.gif'
        self.flame_end_bottom = res_dir + 'resources/images/map/flame_end_bottom.gif'
        self.flame_end_left = res_dir + 'resources/images/map/flame_end_left.gif'
        self.flame_end_right = res_dir + 'resources/images/map/flame_end_right.gif'

        self.portal = res_dir + 'resources/images/map/portal%s.png'
        self.portal_exit = res_dir + 'resources/images/map/portal_gate%d.png'

class FilePathsItems:
    def __init__(self):
        self.coin = res_dir + 'resources/images/map/coin.png'

class FilePathsPlayers:
    def __init__(self):
        self.player_up = res_dir + 'resources/images/player/player_up.gif'
        self.player_down = res_dir + 'resources/images/player/player_down.gif'
        self.player_left = res_dir + 'resources/images/player/player_left.gif'
        self.player_right = res_dir + 'resources/images/player/player_right.gif'

        self.player2_up = res_dir + 'resources/images/player/player2_up.gif'
        self.player2_down = res_dir + 'resources/images/player/player2_down.gif'
        self.player2_left = res_dir + 'resources/images/player/player2_left.gif'
        self.player2_right = res_dir + 'resources/images/player/player2_right.gif'

class FilePathsEffects:
    def __init__(self):
        self.flame_up = res_dir + 'resources/images/effects/flame_up.png'

class FilePathsMonsters:
    def __init__(self):
        self.ghost = res_dir + 'resources/images/monsters/ghost.png'
        self.purple_fluffy = res_dir + 'resources/images/monsters/purple_fluffy.gif'
        self.red_fluffy = res_dir + 'resources/images/monsters/red_fluffy.gif'
        self.black_fluffy = res_dir + 'resources/images/monsters/black_fluffy.gif'
        self.blue_fluffy = res_dir + 'resources/images/monsters/blue_fluffy.gif'

class FilePaths:
    def __init__(self):
        self.map = FilePathsMap()
        self.monsters = FilePathsMonsters()
        self.players = FilePathsPlayers()
        self.effects = FilePathsEffects()
        self.items = FilePathsItems()

file_paths = FilePaths()

class Textures:
    def __init__(self):
        self.space = Image(file_paths.map.space).texture
        self.block = Image(file_paths.map.block).texture
        self.maze = Image(file_paths.map.maze).texture
        self.bomb = Image(file_paths.map.bomb).texture

        self.coin = Image(file_paths.items.coin).texture

        self.player_up = Image(file_paths.players.player_up).texture
        self.player_down = Image(file_paths.players.player_down).texture
        self.player_left = Image(file_paths.players.player_left).texture
        self.player_right = Image(file_paths.players.player_right).texture

        self.player2_up = Image(file_paths.players.player2_up).texture
        self.player2_down = Image(file_paths.players.player2_down).texture
        self.player2_left = Image(file_paths.players.player2_left).texture
        self.player2_right = Image(file_paths.players.player2_right).texture

        self.player = {}
        self.player['top'] = self.player_up
        self.player['bottom'] = self.player_down
        self.player['left'] = self.player_left
        self.player['right'] = self.player_right

        self.player2 = {}
        self.player2['top'] = self.player2_up
        self.player2['bottom'] = self.player2_down
        self.player2['left'] = self.player2_left
        self.player2['right'] = self.player2_right

        self.powerup_flame_up = Image(file_paths.effects.flame_up).texture

        self.ghost = Image(file_paths.monsters.ghost).texture
        self.purple_fluffy = Image(file_paths.monsters.purple_fluffy).texture
        self.red_fluffy = Image(file_paths.monsters.red_fluffy).texture
        self.black_fluffy = Image(file_paths.monsters.black_fluffy).texture
        self.blue_fluffy = Image(file_paths.monsters.blue_fluffy).texture

        self.portals = {}
        for i in range(0,9):
            letter = string.uppercase[i]
            self.portals[letter] = Image(file_paths.map.portal % letter).texture
        self.portal_exits = {}
        for i in range(1,10):
            self.portal_exits[i] = Image(file_paths.map.portal_exit % i).texture

textures = Textures()
