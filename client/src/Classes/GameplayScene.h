#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//#include "SimpleAudioEngine.h"
#include "Gameplay/LevelLayer.h"

class GameplayScene : public CCLayer
{
public:
	GameplayScene();
	~GameplayScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	virtual void menuCloseCallback(cocos2d::CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameplayScene);

	void registerWithTouchDispatcher();
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	//void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);


protected:
    LevelLayer *_levelLayer;
};

#endif  // __HELLOWORLD_SCENE_H__
