#include "LevelSelectLayer.h"

#ifdef _WINDOWS
    #include "../../../lib/dirent/dirent.h"
#else
    #include <dirent.h>
#endif

//
Scene* LevelSelectLayer::scene()
{
    Scene * scene = NULL;
    // 'scene' is an autorelease object
    scene = Scene::create();
    if (!scene)
        return NULL;

    // 'layer' is an autorelease object
    LevelSelectLayer *layer = LevelSelectLayer::create();
    if (!layer)
        return NULL;
    ;
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//
bool LevelSelectLayer::init()
{
    if (!Layer::init())
        return false;

    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Menu* menu = Menu::create();

    // Scan directory
    DIR *dp;
    struct dirent *ep;
     
    dp = opendir ("../Resources/levels");
    if (dp != NULL)
    {
        int position = 0;
        while (ep = readdir (dp))
        {
            // Must be at least 1 character long + .tmx and must not be dir or hidden file
            std::string name (ep->d_name); 
            if( strlen(ep->d_name) >= 5 && ep->d_name[0] != '.' &&
                name.find(".tmx") != std::string::npos)
            {
                ccMenuCallback callback = std::bind(&LevelSelectLayer::playersSelect, this, this, name);

                MenuItemFont *newLevel = new MenuItemFont();
                newLevel->initWithString(
                        ep->d_name,
                        callback
                );
                newLevel->setPosition(ccp(0, position));
                menu->addChild(newLevel);
                position -= 50;
            }
        }
        (void) closedir (dp);
    }
    else
    {
        std::cerr << "Couldn't open the directory containing maps!" << std::endl;
    }

    this->addChild(menu, 1);

    menu->setPosition(
            ccp(
                visibleSize.width/2,
                visibleSize.height - 100
            )
    );

    this->setTouchEnabled(true);

    return true;
}

//
void LevelSelectLayer::playersSelect(Object *sender, std::string levelName)
{
    CCLog("player select from level menu");

    using namespace Bomber::Frontend;
    MenuSelections *ms = MenuSelections::getInstance();
    ms->setLevelName( levelName );

    Scene *pScene = PlayersSelectLayer::scene();
    Director::sharedDirector()->replaceScene(pScene);
}

//
void LevelSelectLayer::registerWithTouchDispatcher()
{
    // TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    Director::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}