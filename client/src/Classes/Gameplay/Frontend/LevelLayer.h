#ifndef __BOMBER_LEVEL_LAYER
#define __BOMBER_LEVEL_LAYER

#include "cocos2d.h"

//#include "SimpleAudioEngine.h"
#include "Map/Map.h"
#include "Map/Bomb.h"
#include "Map/Explosion.h"
#include "Sprites/GameSprite.h"
#include "Sprites/Human.h"
#include "../../Input/ControlLayer.h"
#include "../../Input/ActionDelegates.h"
#include "../Backend/Mediator.h"
#include "../Backend/GameObjects/Sprites/Sprite.h"
#include "Menu/MainMenuLayer.h"
#include "GUIUpdater.h"

namespace Bomber
{
    namespace Frontend
    {
        class LevelLayer : public Layer, public PauseGameDelegate
        {
        public:
            LevelLayer();
            ~LevelLayer();

            // Here's a difference. Method 'init' in cocos2d-x returns bool, 
            // instead of returning 'id' in cocos2d-iphone
            virtual bool init();  

            // there's no 'id' in cpp, so we recommand to return the exactly class pointer
            //static cocos2d::Scene* scene();

            // a selector callback
            // implement the "static node()" method manually
            CREATE_FUNC(LevelLayer);

            void updateGame(float dt);

            //void registerWithTouchDispatcher();
            //void ccTouchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
            //void repositionSprite(float dt);
            //void ccTouchesMoved(cocos2d::Set* touches, cocos2d::Event* event);

            void pauseGameAction() { printf("game paused in level layer\n"); };
            
            // a selector callback
            virtual void menuCloseCallback(cocos2d::Object* pSender);
            virtual void menuPauseCallback(cocos2d::Object* pSender);
            virtual void menuResetCallback(cocos2d::Object* pSender);

        protected:
            ControlLayer *_controlLayer;
            Map *_map;
            std::map<unsigned int, Human *> _players;
            Human *_player1;
            Human *_player2;
            bool _gamePaused;
            unsigned int _lastChangeID;
            GUIUpdater *_gui;
            Common::GameState *_gameState;
            //Backend::Sprite *_controlledSprite;

        private:
            void initControlledSprite();
            void initControlLayer();
            void resetLevel();
            void showFinishMenu();
            void backToMenu();
        };
    }
}

#endif
