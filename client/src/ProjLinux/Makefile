EXECUTABLE = SimpleGame

COCOS_ROOT = ../../lib/cocos2d-x
RAKNET_ROOT = ../../lib/raknet

INCLUDES = -I.. \
		   -I../Classes \
		   -I$(COCOS_ROOT)/cocos2dx/support/tinyxml2 \
		   -I$(RAKNET_ROOT)/sources

SOURCES = Main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/GameplayScene.cpp \
        ../Classes/GameOverScene.cpp \
        ../Classes/Input/Touch/Joystick.cpp \
        ../Classes/Input/Keyboard/Keyboard.cpp \
        ../Classes/Input/ControlLayer.cpp \
        ../Classes/Gameplay/Backend/Mediator.cpp \
        ../Classes/Gameplay/Backend/Logic.cpp \
        ../Classes/Gameplay/Backend/GameStateUpdater.cpp \
        ../Classes/Gameplay/Backend/GameState.cpp \
        ../Classes/Gameplay/Backend/GameObject.cpp \
        ../Classes/Gameplay/Backend/Sprite.cpp \
        ../Classes/Gameplay/Backend/BBomb.cpp \
        ../Classes/Gameplay/Backend/Obstacle.cpp \
        ../Classes/Gameplay/Backend/Primitives/Coordinates.cpp \
        ../Classes/Gameplay/Backend/Primitives/Rectangle.cpp \
        ../Classes/Gameplay/Backend/Statistics/Statistics.cpp \
        ../Classes/Gameplay/Backend/Statistics/StatisticsUpdater.cpp \
        ../Classes/Gameplay/Backend/Statistics/Achievements.cpp \
        ../Classes/Gameplay/Backend/Statistics/AchievementContainer.cpp \
        ../Classes/Gameplay/Backend/Statistics/GameAchievements.cpp \
        ../Classes/Gameplay/Backend/AI/AI.cpp \
        ../Classes/Gameplay/Backend/AI/FollowAI.cpp \
        ../Classes/Gameplay/Frontend/LevelLayer.cpp \
        ../Classes/Gameplay/Frontend/ButtonLayer.cpp \
        ../Classes/Gameplay/Frontend/GameButton.cpp \
        ../Classes/Gameplay/Frontend/ControlButton.cpp \
        ../Classes/Gameplay/Frontend/AchievementButton.cpp \
        ../Classes/Gameplay/Frontend/GUIUpdater.cpp \
        ../Classes/Gameplay/Map/Map.cpp \
        ../Classes/Gameplay/Map/Bomb.cpp \
        ../Classes/Gameplay/Map/Explosion.cpp \
        ../Classes/Gameplay/Sprites/GameSprite.cpp \
        ../Classes/Gameplay/Sprites/Human.cpp \
        ../Classes/Menu/MainMenuLayer.cpp \
        ../Classes/Menu/SettingsLayer.cpp \
        ../Classes/Menu/CreditsLayer.cpp \

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion -lboost_system
CXXFLAGS += -g -lglut -Wunused-variable
RAKNET_LIBS = $(RAKNET_ROOT)/lib/libraknet.so
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so
INCLUDES += -I$(COCOS_ROOT)/CocosDenshion/include
SHAREDLIBS += $(RAKNET_LIBS)

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(RAKNET_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
