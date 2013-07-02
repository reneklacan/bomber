#ifndef __BOMBER_LEVEL_LAYER
#define __BOMBER_LEVEL_LAYER

#include "cocos2d.h"

//#include "SimpleAudioEngine.h"
#include "../Map/Map.h"
#include "../Map/Bomb.h"
#include "../Map/Explosion.h"
#include "../Sprites/GameSprite.h"
#include "../Sprites/Human.h"
#include "../../Input/ControlLayer.h"
#include "../../Input/ActionDelegates.h"

namespace Bomber
{
    namespace Frontend
    {
        class LevelLayer : public CCLayer, public PauseGameDelegate
        {
        public:
            LevelLayer();
            ~LevelLayer();

            // Here's a difference. Method 'init' in cocos2d-x returns bool, 
            // instead of returning 'id' in cocos2d-iphone
            virtual bool init();  

            // there's no 'id' in cpp, so we recommand to return the exactly class pointer
            //static cocos2d::CCScene* scene();

            // a selector callback
            // implement the "static node()" method manually
            CREATE_FUNC(LevelLayer);

            void updateGame(float dt);

            //void registerWithTouchDispatcher();
            //void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
            void repositionSprite(float dt);
            //void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

            void pauseGameAction() { printf("game paused in level layer\n"); };
            
            // a selector callback
            virtual void menuCloseCallback(cocos2d::CCObject* pSender);
            virtual void menuPauseCallback(cocos2d::CCObject* pSender);

        protected:
            ControlLayer *_controlLayer;
            Map *_map;
            Human *_player;
            bool _gamePaused;
            unsigned int _lastChangeID;
        };
    }
}

#endif
