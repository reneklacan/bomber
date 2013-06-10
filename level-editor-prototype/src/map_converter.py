import os
import sys
import json
from lxml import etree


TILE_WIDTH = 101
TILE_HEIGHT = 81

SPAWNPOINT = 1000

SPECIALS = (
        SPAWNPOINT,
)

def json2tmx(category, item):
    json2tmx_table = {
            None: 0,
            'SPACE': 37,
            'MAZE': 20,
            'BLOCK': 42,
            'PORTAL': 15,
            'DEATH_FLAME': 13,
            'COIN': 35,
            'SPAWN': SPAWNPOINT,
    }

    if category == 'portal':
        return json2tmx_table['PORTAL']
    elif category == 'portal_exit':
        return json2tmx_table[None]

    if item not in json2tmx_table:
        print >> sys.stderr, '%s not in convert table' % item
        return json2tmx_table['SPACE']
    return json2tmx_table[item]

class MapLayer:
    def __init__(self, name):
        self.name = name
        self.layout = []

class Map:
    def __init__(self):
        self.width = 0
        self.height = 0
        self.layers = None

    def _get_file_content(self, file_path):
        with open(file_path, 'r') as f:
            return f.read()

    def _save_file(self, file_path, content):
        with open(file_path, 'w') as f:
            f.write(content)

    def load_json_file(self, file_path):
        self.load_json_string(self._get_file_content(file_path))

    def load_tmx_file(self, file_path):
        self.load_tmx_string(self._get_file_content(file_path))

    def load_json_string(self, json_string):
        level = json.loads(json_string)
        
        self.width = level['grid_size'][0]
        self.height = level['grid_size'][1]

        self.layers = (
                MapLayer('floor'),
                MapLayer('obstacles'),
                MapLayer('items'),
                MapLayer('portals'),
        )

        self.portals_location = {}
        self.portal_exits_location = {}
        self.portals_conf = level['portals_conf']

        for i, tile in enumerate(level['layout']):
            self.layers[0].layout.append(json2tmx(*tile[0]))
            self.layers[1].layout.append(json2tmx(*tile[1]))
            self.layers[2].layout.append(json2tmx(*tile[2]))
            self.layers[3].layout.append(json2tmx(*tile[3]))
            
            if tile[3][0] == 'portal':
                self.portals_location[tile[3][1]] = {'x': i%self.width, 'y':i//self.width}
            elif tile[3][0] == 'portal_exit':
                self.portal_exits_location[tile[3][1]] = {'x': i%self.width, 'y':i//self.width}

    def load_tmx_string(self, xml_string):
        pass

    def dump_tmx_string(self):
        map = etree.Element('map')
        map.set('version', '1.0')
        map.set('orientation', 'orthogonal')
        map.set('width', '%d' % self.width)
        map.set('height', '%d' % self.height)
        map.set('tilewidth', '%d' % TILE_WIDTH)
        map.set('tileheight', '%d' % TILE_HEIGHT)

        tileset = etree.Element('tileset')
        tileset.set('firstgid', '1')
        tileset.set('source', 'tileset.tsx')
        map.append(tileset)

        floor_properties = etree.Element('properties')
        property1 = etree.Element('property')
        property1.set('name', 'cc_vertexz')
        property1.set('value', '-40')
        floor_properties.append(property1)

        for each in self.layers:
            layer = etree.Element('layer')
            layer.set('name', each.name)
            layer.set('width', '%d' % self.width)
            layer.set('height', '%d' % self.height)
            data = etree.Element('data')
            empty = True

            if each.name == 'floor':
                layer.append(floor_properties)
            else:
                other_properties = etree.Element('properties')
                property1 = etree.Element('property')
                property1.set('name', 'cc_vertexz')
                property1.set('value', 'automatic')
                other_properties.append(property1)
                property2 = etree.Element('property')
                property2.set('name', 'cc_alpha_func')
                property2.set('value', '0.5')
                other_properties.append(property2)

                layer.append(other_properties)

            for item in each.layout:
                if item in SPECIALS:
                    item = 0
                if item:
                    empty = False
                tile = etree.Element('tile')
                tile.set('gid', '%d' % item)
                data.append(tile)

            if empty:
                layer.set('visible', '0')
            layer.append(data)
            map.append(layer)

        spawnpoints = etree.Element('objectgroup')
        spawnpoints.set('name', 'spawnpoints')
        spawnpoints.set('width', '%d' % self.width)
        spawnpoints.set('height', '%d' % self.height)

        colliders = etree.Element('objectgroup')
        colliders.set('name', 'colliders')
        colliders.set('width', '%d' % self.width)
        colliders.set('height', '%d' % self.height)

        for i, item in enumerate(self.layers[1].layout):
            x = i % self.width
            y = i//self.width
            if not item:
                continue

            if item == SPAWNPOINT:
                obj = etree.Element('object')
                obj.set('name', 'spawnpoint')
                obj.set('x', '%d' % (x*TILE_WIDTH + (TILE_WIDTH/2 - 30/2)))
                obj.set('y', '%d' % (y*TILE_HEIGHT + (TILE_HEIGHT/2 - 30/2)))
                obj.set('width', '30')
                obj.set('height', '30')

                spawnpoints.append(obj)
                continue

            obj = etree.Element('object')
            obj.set('name', '')
            obj.set('x', '%d' % (x*TILE_WIDTH))
            obj.set('y', '%d' % (y*TILE_HEIGHT))
            obj.set('width', '%d' % TILE_WIDTH)
            obj.set('height', '40')

            colliders.append(obj)

        map.append(spawnpoints)
        map.append(colliders)

        portals = etree.Element('objectgroup')
        portals.set('name', 'portals')
        portals.set('width', '%d' % self.width)
        portals.set('height', '%d' % self.height)
        
        for portal, location in self.portals_location.items():
            portal_conf = self.portals_conf[portal]

            x = location['x']
            y = location['y']

            if portal_conf['left'] is not None:
                obj = etree.Element('object')
                obj.set('name', '%d' % portal_conf['left'])
                obj.set('x', '%d' % (x*TILE_WIDTH))
                obj.set('y', '%d' % (y*TILE_HEIGHT + (TILE_HEIGHT/2 - 30/2)))
                obj.set('width', '30')
                obj.set('height', '30')

                portals.append(obj)

            if portal_conf['right'] is not None:
                obj = etree.Element('object')
                obj.set('name', '%d' % portal_conf['right'])
                obj.set('x', '%d' % (x*TILE_WIDTH + TILE_WIDTH - 30))
                obj.set('y', '%d' % (y*TILE_HEIGHT + (TILE_HEIGHT/2 - 30/2)))
                obj.set('width', '30')
                obj.set('height', '30')

                portals.append(obj)

            if portal_conf['top'] is not None:
                obj = etree.Element('object')
                obj.set('name', '%d' % portal_conf['top'])
                obj.set('x', '%d' % (x*TILE_WIDTH + (TILE_WIDTH/2 - 30/2)))
                obj.set('y', '%d' % (y*TILE_HEIGHT))
                obj.set('width', '30')
                obj.set('height', '30')

                portals.append(obj)

            if portal_conf['bottom'] is not None:
                obj = etree.Element('object')
                obj.set('name', '%d' % portal_conf['bottom'])
                obj.set('x', '%d' % (x*TILE_WIDTH + (TILE_WIDTH/2 - 30/2)))
                obj.set('y', '%d' % (y*TILE_HEIGHT + TILE_HEIGHT - 30))
                obj.set('width', '30')
                obj.set('height', '30')

                portals.append(obj)

        map.append(portals)

        portal_exits = etree.Element('objectgroup')
        portal_exits.set('name', 'portal_exits')
        portal_exits.set('width', '%d' % self.width)
        portal_exits.set('height', '%d' % self.height)

        for exit, location in self.portal_exits_location.items():
            x = location['x']
            y = location['y']

            obj = etree.Element('object')
            obj.set('name', '%d' % exit)
            obj.set('x', '%d' % (x*TILE_WIDTH + (TILE_WIDTH/2 - 30/2)))
            obj.set('y', '%d' % (y*TILE_HEIGHT + (TILE_HEIGHT/2 - 30/2)))
            obj.set('width', '30')
            obj.set('height', '30')
            portal_exits.append(obj)

        map.append(portal_exits)

        header = '<?xml version="1.0" encoding="UTF-8"?>\n'
        return header + etree.tostring(map, pretty_print=True)

    def dump_json_string(self):
        pass

    def dump_json_file(self, file_path):
        self._save_file(file_path, self.dump_json_string())

    def dump_tmx_file(self, file_path):
        self._save_file(file_path, self.dump_tmx_string())

def main():
    map = Map()
    if len(sys.argv) == 1:
        map.load_json_file('levels/kocky.json')
    else:
        map.load_json_file(sys.argv[0])

    print map.dump_tmx_string()

if __name__ == '__main__':
    main()
