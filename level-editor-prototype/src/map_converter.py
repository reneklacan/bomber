import os
import sys
import json
import tmx.etree.ElementTree as etree

class MapLayout:
    def __init__(self):
        pass

class Map:
    def __init__(self):
        self.width = 0
        self.height = 0
        self.layouts = None

    def _get_file_content(file_path):
        with open(file_path, 'r') as f:
            return f.read()

    def _save_file(file_path, content):
        with open(file_path, 'w') as f:
            f.write(content)

    def load_json_file(file_path):
        self.load_json_string(self.get_file_content(file_path))

    def load_tmx_file(file_path):
        self.load_tmx_string(self.get_file_content(file_path))

    def load_json_string(json_string):
        level = json.loads(json_string)
        
        self.width = level['grid_size'][0]
        self.height = level['grid_size'][1]

    def load_tmx_string(xml_string):
        pass

    def dump_tmx_string():
        pass

    def dump_json_string():
        pass

    def dump_json_file(file_path):
        self._save_file(self.dump_json_string())

    def dump_tmx_file(file_path):
        self._save_file(self.dump_tmx_string())

def main():
    map = Map()
    map.load_json_file('levels/test.json')

if __name__ == '__main__':
    main()
