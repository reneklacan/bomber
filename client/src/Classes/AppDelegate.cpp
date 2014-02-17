#include "AppDelegate.h"
#include "GameplayScene.h"
#include "Menu/MainMenuLayer.h"
#include "Menu/LevelSelectLayer.h"

USING_NS_CC;


AppDelegate::AppDelegate() {
    _levelToLaunch = nullptr;
}

AppDelegate::AppDelegate(char *level) {
    _levelToLaunch = level;
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director *pDirector = Director::sharedDirector();

    pDirector->setOpenGLView(EGLView::sharedOpenGLView());

    Size screenSize = EGLView::sharedOpenGLView()->getFrameSize();
    //Size designSize = CCSizeMake(1600, 900);
    Size designSize = CCSizeMake(12*101, 12*81);
    std::vector<std::string> searchPaths;

    if (screenSize.height > 320)
    {
        searchPaths.push_back("hd");
        searchPaths.push_back("sd");
        Size resourceSize = CCSizeMake(12*101, 12*81);
        //pDirector->setContentScaleFactor(960.0f/designSize.height);
        ///pDirector->setContentScaleFactor(1.0f);
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    else
    {
        searchPaths.push_back("sd");
        pDirector->setContentScaleFactor(640.0f/designSize.height);
    }

    FileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

    EGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //Scene *pScene = GameplayScene::scene();
    Scene *scene;

    if (_levelToLaunch == nullptr)
    {
        scene = MainMenuLayer::scene();
    }
    else
    {
        auto ms = Bomber::Frontend::MenuSelections::getInstance();
        ms->setLevelFilename(_levelToLaunch);
        ms->setLevelName("test");
        scene = GameplayScene::scene();
    }

    // run
    pDirector->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
