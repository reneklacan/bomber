#!/bin/env python2

from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from editor import Wizard

class BomberLevelEditor(App):
    def build(self):
        self.root = MainWidget()

    def on_stop(self):
        self.root.game.restart()

class MainWidget(BoxLayout):
    def __init__(self, **kwargs):
        BoxLayout.__init__(self, orientation='horizontal')
        self.initialized = False

    def on_size(self, mw, size):
        if not self.initialized:
            self.clear_widgets()
            self.add_widget(Wizard())
            self.initialized = True

if __name__ in ('__main__', '__android__'):
    try:
        app = BomberLevelEditor()
        app.use_kivy_settings = True
        app.run()
    except KeyboardInterrupt:
        pass
