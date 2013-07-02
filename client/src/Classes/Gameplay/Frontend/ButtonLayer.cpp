#include "ButtonLayer.h"

using namespace Bomber::Frontend;

//
ButtonLayer *ButtonLayer::getInstance()
{
    static ButtonLayer instance;
    return &instance;
}

//
void ButtonLayer::addToSkills(GameButton *skill)
{
    _skills.push_back(skill);
}

//
void ButtonLayer::addToBuffs(GameButton *buff)
{
    _buffs.push_back(buff);
}

//
void ButtonLayer::addToAchievementss(GameButton *achievement)
{
    _achievements.push_back(achievement);
}

//
void ButtonLayer::addToControls(GameButton *control)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCPoint *last = new CCPoint();
    last->x = origin.x + visibleSize.width;
    last->y = origin.y + visibleSize.height;

    if(_controls.size() > 0)
    {
        last = _controls.back()->getButtonPosition();
    }

    CCPoint *next = new CCPoint();
    next->x = last->x - control->getWidth();
    next->y = origin.y + visibleSize.height - control->getHeight(); 

    control->setButtonPosition(next);

    _controls.push_back(control);
}