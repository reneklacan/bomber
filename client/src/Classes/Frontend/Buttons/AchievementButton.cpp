#include "AchievementButton.h"

using namespace Bomber::Frontend;

AchievementButton::AchievementButton(std::string title, std::string description, std::string image)
: _width(300), _height(32)
{
    Node *achieveButton = new Node();

    Sprite *bcg = new Sprite();
    bcg->initWithFile("tiles/achievement.png");
    //bcg->setContentSize( Size(300, 200) );
    //bcg->setColor( ccc3(255, 255, 255) );

    LabelTTF* achieveTitle = LabelTTF::create(
        title.c_str(),
        "Helvetica",
        32,
        CCSizeMake(_width, _height), 
        kTextAlignmentCenter
    );
    LabelTTF* achieveDescription = LabelTTF::create(
        description.c_str(),
        "Helvetica",
        24,
        CCSizeMake(_width, _height), 
        kTextAlignmentCenter
    );

    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    bcg->setPosition(
        ccp(
            visibleSize.width/2,
            visibleSize.height - _height*2.5
        )
    );
    achieveTitle->setPosition( 
        ccp(
            visibleSize.width/2,
            visibleSize.height - _height*2
        )
    );
    achieveDescription->setPosition( 
        ccp(
            visibleSize.width/2,
            visibleSize.height - _height*3
        )
    );

    achieveButton->addChild(bcg, 1);
    achieveButton->addChild(achieveTitle, 1);
    achieveButton->addChild(achieveDescription, 1);

    _button = achieveButton;
}