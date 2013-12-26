#include "LevelSelectLayer.h"
#include "../Common/Storage/XMLStorage.h"

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

    // map filenames to level names
    _levelNameMap["00.tmx"] = "0. Test Level";
    _levelNameMap["01.tmx"] = "1. Test Level";
    _levelNameMap["02.tmx"] = "2. Test Level";

    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Menu* menu = Menu::create();

    // Scan directory
    DIR *dp;
    struct dirent *ep;

    std::vector<std::string> files;
     
    dp = opendir("../Resources/levels");
    if (dp != NULL)
    {
        while (ep = readdir(dp))
        {
            std::string name(ep->d_name);

            // Must contain .tmx and must not be dir or hidden file
            if (name[0] != '.' && name.find(".tmx") != std::string::npos)
                files.push_back(name);
        }
        (void) closedir(dp);
        std::sort(files.begin(), files.end());
    }
    else
    {
        std::cerr << "Couldn't open the directory containing maps!" << std::endl;
    }

    int position = 0;

    Bomber::Common::XMLStorage *storage = Bomber::Common::XMLStorage::getInstance();

    for (auto filename : files)
    {
        if (_levelNameMap.count(filename) == 0)
        {
            std::cerr << "Not defined level name for filename " << filename << std::endl;
            continue;
        }

        ccMenuCallback callback = std::bind(&LevelSelectLayer::playersSelect, this, this, filename);

        MenuItemFont *newLevel = new MenuItemFont();

        std::string nameToDisplay(_levelNameMap[filename]);

        if (storage->get("level_status", filename) != "")
        {
            nameToDisplay += " - ";
            nameToDisplay += storage->get("level_status", filename);
        }

        newLevel->initWithString(
            nameToDisplay.c_str(),
            callback
        );
        newLevel->setPosition(ccp(0, position));
        menu->addChild(newLevel);
        position -= 50;
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
void LevelSelectLayer::playersSelect(Object *sender, std::string filename)
{
    CCLog("player select from level menu");

    using namespace Bomber::Frontend;
    MenuSelections *ms = MenuSelections::getInstance();
    ms->setLevelFilename(filename);
    ms->setLevelName(_levelNameMap[filename]);

    //Scene *pScene = PlayersSelectLayer::scene();
    //Director::sharedDirector()->replaceScene(pScene);
    
    CCLog("skipping player select menu");

    // skip players amount selection
    Scene *pScene = GameplayScene::scene();
    Director::sharedDirector()->replaceScene(pScene);
}

//
void LevelSelectLayer::registerWithTouchDispatcher()
{
    // TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    Director::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}
