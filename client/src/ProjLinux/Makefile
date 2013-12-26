EXECUTABLE = bomber

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
        ../Classes/Configuration.cpp \
        ../Classes/Common/Primitives/Coordinates.cpp \
        ../Classes/Common/Primitives/Rectangle.cpp \
        ../Classes/Common/GameState/GameState.cpp \
        ../Classes/Common/Cache/ObjectCache.cpp \
        ../Classes/Common/Storage/XMLStorage.cpp \
        ../Classes/Backend/Mediator.cpp \
        ../Classes/Backend/Logic.cpp \
        ../Classes/Backend/GameState/GameStateUpdater.cpp \
        ../Classes/Backend/GameObjects/GameObject.cpp \
        ../Classes/Backend/GameObjects/Sprites/Sprite.cpp \
        ../Classes/Backend/GameObjects/BBomb.cpp \
        ../Classes/Backend/GameObjects/Obstacle.cpp \
        ../Classes/Backend/GameObjects/Effect.cpp \
        ../Classes/Backend/GameObjects/Portal.cpp \
        ../Classes/Backend/Interactions/Movement.cpp \
        ../Classes/Backend/Statistics/Statistics.cpp \
        ../Classes/Backend/Statistics/StatisticsUpdater.cpp \
        ../Classes/Backend/Statistics/Achievements.cpp \
        ../Classes/Backend/Statistics/AchievementContainer.cpp \
        ../Classes/Backend/Statistics/GameAchievements.cpp \
        ../Classes/Backend/AI/AI.cpp \
        ../Classes/Backend/AI/FollowAI.cpp \
        ../Classes/Frontend/LevelLayer.cpp \
        ../Classes/Frontend/ButtonLayer.cpp \
        ../Classes/Frontend/Collisions.cpp \
        ../Classes/Frontend/Buttons/GameButton.cpp \
        ../Classes/Frontend/Buttons/ControlButton.cpp \
        ../Classes/Frontend/Buttons/AchievementButton.cpp \
        ../Classes/Frontend/Buttons/EffectButton.cpp \
        ../Classes/Frontend/GUIUpdater.cpp \
        ../Classes/Frontend/Map/Map.cpp \
        ../Classes/Frontend/Map/Explosion.cpp \
        ../Classes/Frontend/Sprites/GameSprite.cpp \
        ../Classes/Frontend/Sprites/Human.cpp \
        ../Classes/Frontend/Sprites/SpriteCreator.cpp \
        ../Classes/Frontend/Cache/GUICache.cpp \
        ../Classes/Menu/MainMenuLayer.cpp \
        ../Classes/Menu/SettingsLayer.cpp \
        ../Classes/Menu/CreditsLayer.cpp \
        ../Classes/Menu/LevelSelectLayer.cpp \
        ../Classes/Menu/PlayersSelectLayer.cpp \
        ../Classes/Middend/NetClient.cpp \

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion #-lboost_system
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
