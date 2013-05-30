
import os
import json
import string
from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.relativelayout import RelativeLayout
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.scrollview import ScrollView
from kivy.graphics import Rectangle
from components import file_paths, textures
from constants import *
import monsters
from monsters import *

def convert2int(num):
    try:
        return int(num)
    except ValueError:
        return None

def convert2str(s):
    if s is None:
        return None
    return str(s)

class Wizard(FloatLayout):
    def __init__(self, **kwargs):
        FloatLayout.__init__(self, **kwargs)

        self.level_select()
        #self.info_input()

    def level_select(self):
        self.clear_widgets()

        levels_layout = BoxLayout(orientation='vertical', spacing=50, padding=50)

        topmenu = BoxLayout(
                orientation='horizontal',
        )
        topmenu.add_widget(Label())
        topmenu.add_widget(Label())

        levels_layout.add_widget(topmenu)

        def delete_level(btn):
            os.remove('levels/' + btn.filename)
            self.level_select()

        for level_filename in os.listdir('levels'):
            if not level_filename.endswith('.json'):
                continue
            
            with open('levels/' + level_filename) as f:
                level = json.loads(f.read())

            level_layout = BoxLayout(orientation='horizontal', spacing=50)
            level_layout.add_widget(Label(text=level['name']))

            edit_button = Button(
                    text='Edit',
                    on_release=lambda btn: self.load_level(btn.level)
            )
            edit_button.level = level
            level_layout.add_widget(edit_button)

            delete_button = Button(
                    text='Delete',
                    on_release = delete_level,
            )
            delete_button.filename = level_filename
            level_layout.add_widget(delete_button)

            levels_layout.add_widget(level_layout)

        levels_layout.add_widget(
                Button(
                    text='New level',
                    on_release=lambda btn: self.info_input()
                )
        )
        self.add_widget(levels_layout)

    def load_level(self, level):
        self.name = level['name']
        self.grid_width = level['grid_size'][0]
        self.grid_height = level['grid_size'][1]

        self.grid_setup(level)

    def info_input(self):
        self.clear_widgets()
        self.info = InfoInput(
                size_hint=(None,None),
                size=(400, 200),
        )
        self.add_widget(self.info)
        self.info.init()

    def grid_setup(self, level=None):
        self.clear_widgets()

        self.grid = GridSetup(
                size_hint=(1,1),
                level=level,
        )
        self.add_widget(self.grid)
        #self.grid_setup.init()

    def export(self):
        level = {}
        level['name'] = self.name

        level['layout'] = []
        for tile in self.grid.tiles:
            item = (
                    (tile.primary_category,      tile.primary_item),
                    (tile.secondary_category,    convert2str(tile.secondary_item)),
                    (tile.tertiary_category,     tile.tertiary_item),
            )
            level['layout'].append(item)

        level['portals_conf'] = self.grid.portals_conf
        level['monster_dict'] = {}
        for monster in monsters.registered:
            level['monster_dict'][monster.shortcut] = monster.__name__

        #level['effects_propability'] = {
        #        "FlameUpEffect": 0.4
        #}
        level['grid_size'] = [
                self.grid_width,
                self.grid_height
        ]

        level_name = level['name'].lower().replace(' ', '_')
        with open('levels/' + level_name + '.json', 'w') as f:
            f.write(json.dumps(level, indent=4))

class Tile(RelativeLayout):
    def __init__(self, **kwargs):
        RelativeLayout.__init__(self, **kwargs)

        self.primary_item = SPACE
        self.secondary_item = None
        self.tertiary_item = None

        self.primary_category = 'map'
        self.secondary_category = None
        self.tertiary_category = None

    def to_space(self):
        texture = textures.space

        self.rectangle = Rectangle(
                texture=texture,
                pos=(0,0),
                size=self.size,
        )
        self.canvas.add(self.rectangle)

    def on_touch_down(self, touch):
        if not self.collide_point(*touch.pos):
            return

        item = self.parent.parent.parent.current_item
        category = self.parent.parent.parent.current_category

        if item is None or category is None:
            return

        if category in ('tertiary', 'portal_exit', 'portal'):
            self.tertiary_item = item
            self.tertiary_category = category
            if item == CLEAR:
                self.tertiary_item = None
                self.tertiary_category = None
        elif category in ('secondary', 'item', 'monsters'):
            self.secondary_item = item
            self.secondary_category = category
            if item == CLEAR:
                self.secondary_item = None
                self.secondary_category = None
        else:
            self.primary_item = item
            self.primary_category = category
            if item == CLEAR:
                self.primary_item = None
                self.primary_category = None
                self.secondary_item = None
                self.secondary_category = None
                self.tertiary_item = None
                self.tertiary_category = None

        self.update()

    def update(self):
        self.to_space()

        if self.primary_category is not None:
            if self.primary_category == 'map':
                if self.primary_item == SPAWNPOINT:
                    texture = textures.player_up
                if self.primary_item == SPACE:
                    texture = textures.space
                elif self.primary_item == BLOCK:
                    texture = textures.block
                elif self.primary_item == MAZE:
                    texture = textures.maze
                elif self.primary_item is None:
                    self.canvas.clear()
                    return
                else:
                    print 'Unknown primary item: %s' % self.primary_item
            else:
                print 'Unknown primary category: %s' % self.primary_item

            self.rectangle = Rectangle(
                    texture=texture,
                    pos=(0,0),
                    size=self.size,
            )
            self.canvas.add(self.rectangle)
        else:
            self.canvas.clear()
            return

        if self.secondary_item is not None:
            if self.secondary_category == 'item':
                if self.secondary_item == COIN:
                    texture = textures.coin
                elif self.secondary_item == POWERUP_FLAME_UP:
                    texture = textures.powerup_flame_up
                else:
                    print 'Unknown secondary item: %s' % self.secondary_item
            elif self.secondary_category == 'monsters':
                self.secondary_item = self.secondary_item
                texture = self.secondary_item.cls_texture
            else:
                print 'Unknown secondary category: %s' % self.secondary_category

            self.rectangle = Rectangle(
                    texture=texture,
                    pos=(0,0),
                    size=self.size,
            )
            self.canvas.add(self.rectangle)

        if self.tertiary_item is not None:
            if self.tertiary_category == 'portal_exit':
                texture = textures.portal_exits[self.tertiary_item]
            elif self.tertiary_category == 'portal':
                texture = textures.portals[self.tertiary_item]
            else:
                print 'Unknown tertiary category: %s' % self.tertiary_category

            self.rectangle = Rectangle(
                    texture=texture,
                    pos=(0,0),
                    size=self.size,
            )
            self.canvas.add(self.rectangle)

    def on_touch_move(self, movement):
        self.on_touch_down(movement)

    def load(self, level, index):
        item = level['layout'][index]
        self.primary_category, self.primary_item = item[0]
        self.secondary_category, self.secondary_item = item[1]
        self.tertiary_category, self.tertiary_item = item[2]
        if self.secondary_category == 'monsters':
            self.secondary_item = eval('monsters.' + level['monster_dict'][self.secondary_item])()
        self.update()

class GridSetup(BoxLayout):
    def __init__(self, **kwargs):
        BoxLayout.__init__(self, orientation='horizontal', **kwargs)
        self.level = kwargs['level']
        self.current_item = None
        self.current_category = None
        self.portal_counter = 0
        self.portal_widget = None
        self.portal_exit_counter = 0
        self.portals_conf = {}

    def on_size(self, grid, size):
        self.clear_widgets()
        self.init()

    def init(self):
        self.grid = GridLayout(
                cols=self.parent.grid_width,
                size_hint=(1, None),
        )

        width = self.parent.grid_width
        height = self.parent.grid_height

        tile_size = self.size[0] * 0.8 / width
        self.grid.size = (tile_size * width, tile_size * height)
        
        if self.level is not None:
            self.portals_conf = self.level['portals_conf']

        # TODO is self.level is not None
        self.tiles = []
        for i in range(width * height):
            tile = Tile(
                size=(tile_size, tile_size),
                size_hint=(None, None)
            )
            tile.ix = i % width
            tile.iy = i // width
            tile.to_space()
            if self.level is not None:
                tile.load(self.level, i)
            self.tiles.append(tile)
            self.grid.add_widget(tile)

        self.sidebar = BoxLayout(
                orientation='vertical',
                size_hint=(1, 1.5),
        )
        self.sidescroll = ScrollView(size_hint=(0.2, 1))
        self.sidescroll.do_scroll_x = False
        self.sidescroll.add_widget(self.sidebar)

        self.sidebar.add_widget(Label(text='[b]Primary category[/b]', markup = True))
        self.sidebar.add_widget(
                Button(
                    text='Clear',
                    on_release=lambda btn: self.change_tool('primary', CLEAR),
                )
        )
        self.sidebar.add_widget(Label(text='Tiles:'))
        self.sidebar.add_widget(
                Button(
                    text='Spawnpoint',
                    on_release=lambda btn: self.change_tool('map', SPAWNPOINT),
                )
        )
        self.sidebar.add_widget(
                Button(
                    text='Void',
                    on_release=lambda btn: self.change_tool('map', CLEAR),
                )
        )
        self.sidebar.add_widget(
                Button(
                    text='Space',
                    on_release=lambda btn: self.change_tool('map', SPACE),
                )
        )
        self.sidebar.add_widget(
                Button(
                    text='Block',
                    on_release=lambda btn: self.change_tool('map', BLOCK),
                )
        )
        self.sidebar.add_widget(
                Button(
                    text='Maze',
                    on_release=lambda btn: self.change_tool('map', MAZE),
                )
        )

        self.sidebar.add_widget(Label(text='[b]Secondary category[/b]', markup = True))
        self.sidebar.add_widget(
                Button(
                    text='Clear',
                    on_release=lambda btn: self.change_tool('secondary', CLEAR),
                )
        )
        self.sidebar.add_widget(Label(text='Items:'))
        self.sidebar.add_widget(
                Button(
                    text='Coin',
                    on_release=lambda btn: self.change_tool('item', COIN),
                )
        )
        self.sidebar.add_widget(
                Button(
                    text='Flame up',
                    on_release=lambda btn: self.change_tool('item', POWERUP_FLAME_UP),
                )
        )

        self.sidebar.add_widget(Label(text='Monsters:'))

        for monster_cls in monsters.registered:
            button = Button(
                text=monster_cls.name,
                on_release=lambda btn: self.change_tool(btn.category, btn.monster),
            )
            button.category = 'monsters'
            button.monster = monster_cls()
            self.sidebar.add_widget(button)

        self.sidebar.add_widget(Label(text='[b]Tertiary category[/b]', markup = True))
        self.sidebar.add_widget(
                Button(
                    text='Clear',
                    on_release=lambda btn: self.change_tool('tertiary', CLEAR),
                )
        )
        self.sidebar.add_widget(Label(text='Portals:'))
        self.sidebar.add_widget(
                Button(
                    text='New portal',
                    on_release=lambda btn: self.change_tool('portal_new', 0),
                )
        )
        self.sidebar.add_widget(
                Button(
                    text='New portal exit',
                    on_release=lambda btn: self.change_tool('portal_exit_new', 0),
                )
        )
        self.sidebar.add_widget(Label(size_hint_y=0.3))

        self.main = BoxLayout(
                orientation='vertical',
                size_hint=(0.8, 1),
        )
        self.topbar = BoxLayout(
                orientation='horizontal',
                size_hint=(1, None),
                size=(0, 40),
        )
        self.topbar.add_widget(
                Button(
                    text='Edit another level',
                    on_release=lambda btn: self.parent.level_select(),
                )
        )
        self.topbar.add_widget(Label(text=''))
        self.topbar.add_widget(
                Button(
                    text='Save level',
                    on_release=lambda btn: self.parent.export(),
                )
        )
        self.main.add_widget(self.topbar)
        self.main.add_widget(FloatLayout())
        self.main.add_widget(self.grid)

        self.add_widget(self.main)
        #self.sidebar.size_hint_y = len(self.sidebar.children)/25.0
        self.add_widget(self.sidescroll)

    def change_tool(self, category, item):
        self.current_category = category
        self.current_item = item

        if category == 'portal_new':
            self.portal_counter += 1
            portal_id = string.uppercase[self.portal_counter - 1]
            btn = Button(
                text='Portal %s' % portal_id,
                on_release=lambda btn: self.change_tool('portal', btn.portal_id),
            )
            btn.portal_id = portal_id
            self.sidebar.add_widget(btn)
            self.current_item = portal_id

            self.change_tool('portal', portal_id)

        elif category == 'portal_exit_new':
            self.portal_exit_counter += 1
            btn = Button(
                text='Portal exit %d' % self.portal_exit_counter,
                on_release=lambda btn: self.change_tool('portal_exit', btn.portal_id),
            )
            btn.portal_id = self.portal_exit_counter
            self.sidebar.add_widget(btn)
            self.current_item = self.portal_exit_counter

            self.change_tool('portal_exit', self.portal_exit_counter)

        elif category == 'portal':
            if self.portal_widget is not None:
                self.sidebar.remove_widget(self.portal_widget)
            gl = GridLayout(cols=2, size_hint_y=4.0)
            gl.add_widget(Label(text='Portal %s:' % item))
            gl.add_widget(Label(text=''))

            default_values = {
                    'top': '', 'right': '', 'bottom': '', 'left': ''
            }

            if item in self.portals_conf:
                for direction, value in self.portals_conf[item].items():
                    if value is None: continue
                    default_values[direction] = str(value)

            gl.add_widget(Label(text='Top ->'))
            top_input = TextInput(text=default_values['top'])
            top_input.bind(text=lambda _,__: self.save_portal_conf())
            gl.add_widget(top_input)
            gl.top_input = top_input

            gl.add_widget(Label(text='Right ->'))
            right_input = TextInput(text=default_values['right'])
            right_input.bind(text=lambda _,__: self.save_portal_conf())
            gl.add_widget(right_input)
            gl.right_input = right_input

            gl.add_widget(Label(text='Bottom ->'))
            bottom_input = TextInput(text=default_values['bottom'])
            bottom_input.bind(text=lambda _,__: self.save_portal_conf())
            gl.add_widget(bottom_input)
            gl.bottom_input = bottom_input

            gl.add_widget(Label(text='Left ->'))
            left_input = TextInput(text=default_values['left'])
            left_input.bind(text=lambda _,__: self.save_portal_conf())
            gl.add_widget(left_input)
            gl.left_input = left_input

            self.portal_widget = gl
            self.sidebar.add_widget(gl)

    def save_portal_conf(self):
        self.portals_conf[self.current_item] = {
                'top':      convert2int(self.portal_widget.top_input.text),
                'right':    convert2int(self.portal_widget.right_input.text),
                'bottom':   convert2int(self.portal_widget.bottom_input.text),
                'left':     convert2int(self.portal_widget.left_input.text),
        }

class InfoInput(GridLayout):
    def __init__(self, **kwargs):
        GridLayout.__init__(self, cols=2, **kwargs)

    def init(self):
        self.width_input = TextInput(text='21')
        self.height_input = TextInput(text='11')
        self.name_input = TextInput(text='level_name')

        self.add_widget(Label(text='Level name:', markup=True))
        self.add_widget(self.name_input)

        self.add_widget(Label(text='Width:', markup=True))
        self.add_widget(self.width_input)

        self.add_widget(Label(text='Height:', markup=True))
        self.add_widget(self.height_input)

        self.add_widget(FloatLayout())
        button = Button(text='Continue')
        button.bind(on_release=lambda btn: self.finish())
        self.add_widget(button)

    def finish(self):
        self.parent.name = self.name_input.text
        self.parent.grid_width = int(self.width_input.text)
        self.parent.grid_height = int(self.height_input.text)
        self.parent.grid_setup()

class LevelEditor(App):
    def build(self):
        self.root = Wizard()

if __name__ in ('__main__', '__android__'):
    try:
        app = LevelEditor()
        app.run()
    except KeyboardInterrupt:
        pass
