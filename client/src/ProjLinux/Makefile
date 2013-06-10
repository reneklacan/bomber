EXECUTABLE = SimpleGame

INCLUDES = -I.. -I../Classes

SOURCES = Main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/GameplayScene.cpp \
        ../Classes/GameOverScene.cpp \
        ../Classes/Input/Joystick.cpp \
        ../Classes/Input/Keyboard.cpp \
        ../Classes/Input/ControlLayer.cpp \
        ../Classes/Gameplay/LevelLayer.cpp \
        ../Classes/Gameplay/Map/Map.cpp \
        ../Classes/Gameplay/Map/Bomb.cpp \
        ../Classes/Gameplay/Map/Explosion.cpp \
        ../Classes/Gameplay/Sprites/GameSprite.cpp \
        ../Classes/Gameplay/Sprites/Human.cpp \

COCOS_ROOT = ../../lib/cocos2d-2.1rc0-x-2.1.3
COCOS_ROOT = ../../lib/cocos2d-x
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion
CXXFLAGS += -g -lglut -Wunused-variable
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so
INCLUDES += -I$(COCOS_ROOT)/CocosDenshion/include

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
