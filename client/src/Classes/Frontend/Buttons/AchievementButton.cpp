#include "AchievementButton.h"

using namespace Bomber::Frontend;

AchievementButton::AchievementButton(std::string title, std::string description, std::string image)
: _width(300), _height(32)
{
    Node *achieveButton = new Node();

    Sprite *icon = new Sprite();
    icon->initWithFile("tiles/images/test_08.png");
    icon->setScale(0.35f);
    Rect bBox = icon->boundingBox();
    int bBoxWidth = bBox.getMaxX() - bBox.getMinX();

    LayerColor *lc = new LayerColor();
    lc->initWithColor( ccc4(10, 10, 10, 220), _width+bBoxWidth, _height*4);

    LabelTTF* achieveTitle = LabelTTF::create(
        title.c_str(),
        TEXT_FONT,
        _height,
        CCSizeMake(_width-bBoxWidth, _height), 
        kTextAlignmentCenter
    );
    LabelTTF* achieveDescription = LabelTTF::create(
        description.c_str(),
        TEXT_FONT,
        _height * 0.6,
        CCSizeMake(_width+bBoxWidth/2, _height), 
        kTextAlignmentCenter
    );

    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    lc->setPosition(
        ccp(
            visibleSize.width/2 - _width/2,
            visibleSize.height
        )
    );

    icon->setPosition(
        ccp(
            bBoxWidth,
            3*_height
        )
    );

    achieveTitle->setPosition( 
        ccp(
            _width/2 + bBoxWidth,
            3*_height
        )
    );
    achieveDescription->setPosition( 
        ccp(
            _width/2 + bBoxWidth/2,
            _height
        )
    );

    achieveButton->addChild(lc, 1);
    lc->addChild(icon, 1);
    lc->addChild(achieveTitle, 1);
    lc->addChild(achieveDescription, 1);

    _button = achieveButton;
}