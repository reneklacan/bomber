#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//#include "SimpleAudioEngine.h"
#include "Frontend/LevelLayer.h"

using namespace Bomber::Frontend;

class GameplayScene : public Layer
{
public:
	GameplayScene();
	~GameplayScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::Scene* scene();

	// a selector callback
	virtual void menuCloseCallback(cocos2d::Object* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameplayScene);

	void registerWithTouchDispatcher();
	void ccTouchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
	//void ccTouchesMoved(cocos2d::Set* touches, cocos2d::Event* event);


protected:
    LevelLayer *_levelLayer;
};

#endif  // __HELLOWORLD_SCENE_H__
