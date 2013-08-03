#include "ButtonLayer.h"

using namespace Bomber::Frontend;

//
ButtonLayer *ButtonLayer::getInstance()
{
    static ButtonLayer instance;
    return &instance;
}

//
ButtonLayer::ButtonLayer()
{
    _skills.clear();
    _achievements.clear();
    _buffs.clear();
    _controls.clear();
    _saveTime = false;
    _time = 0;
}

//
void ButtonLayer::saveTime(float dt)
{
    if(_saveTime)
    {
        _time += dt;
    }

    if(_time >= 5)
    {
        this->removeAchievement();
    }
}

//
void ButtonLayer::setMainLayer(Layer *main)
{
    _mainLayer = main;
}

//
void ButtonLayer::addToSkills(GameButton *skill)
{
    _skills.push_back(skill);
}

//
void ButtonLayer::addToBuffs(GameButton *buff)
{
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Point origin = Director::sharedDirector()->getVisibleOrigin();

    unsigned int gap = 0;   // Offset from other button, real offset is 2*gap

    Point *last = new Point();
    Point *next = new Point();

    if(_buffs.size() > 0)
    {
        for(auto it : _buffs)
        {
            unsigned int ebWidth = it->getWidth();
            Point *bp = it->getButtonPosition();
            Point *new_bp = new Point();
            new_bp->x = bp->x - ebWidth/2 - gap;
            new_bp->y = bp->y;
            it->setButtonPosition(new_bp);
        }
        last = _buffs.back()->getButtonPosition();
        next->x = last->x + buff->getWidth() + 2*gap;
        next->y = last->y;
    }
    else
    {
        next->x = origin.x + visibleSize.width/2 - buff->getWidth()/2;
        next->y = origin.y + 20;    // Offset from bottom border
    }

    buff->setButtonPosition(next);

    _buffs.push_back(buff);
    _mainLayer->addChild(buff->getGameButton(), 1);
}

//
void ButtonLayer::addToAchievements(GameButton *achievement)
{
    _achievements.push_back(achievement);
    this->addAchievement();
}

//
void ButtonLayer::addToControls(GameButton *control)
{
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Point origin = Director::sharedDirector()->getVisibleOrigin();

    Point *last = new Point();
    last->x = origin.x + visibleSize.width;
    last->y = origin.y + visibleSize.height;

    if(_controls.size() > 0)
    {
        last = _controls.back()->getButtonPosition();
    }

    Point *next = new Point();
    next->x = last->x - control->getWidth();
    next->y = origin.y + visibleSize.height - control->getHeight(); 

    control->setButtonPosition(next);

    _controls.push_back(control);
    _mainLayer->addChild(control->getGameButton(), 1);
}

//
void ButtonLayer::addAchievement()
{
    if(!_saveTime)
    {
        _mainLayer->addChild(_achievements[0]->getGameButton(), 1);
        _saveTime = true;
        _time = 0;
    }
}

//
void ButtonLayer::removeAchievement()
{
    GameButton* ac = _achievements[0];
    _achievements.erase(_achievements.begin());
    _mainLayer->removeChild(ac->getGameButton(), true);
    _saveTime = false;
    _time = 0;
    if(_achievements.size() > 0)
    {
        this->addAchievement();
    }
}

//
bool ButtonLayer::isInBuffs(unsigned int id)
{
    for(auto it : _buffs)
    {
        EffectButton *eb = (EffectButton *)it;
        if(eb->getID() == id)
        {
            return true;
        }
    }
    return false;
}

//
void ButtonLayer::incrementBuff(unsigned int id)
{
    for(auto it : _buffs) // MUST be optimized
    {
        EffectButton *eb = (EffectButton *)it;
        if(eb->getID() == id)
        {
            eb->incrementLabel();
        }
    }
}

//
void ButtonLayer::reset()
{
    // Reset buffs
    for(auto it : _buffs)
    {
        _mainLayer->removeChild(it->getGameButton());
    }
    _buffs.clear();
    // Reset achievements
    _saveTime = false;
    _time = 0;
    for(auto it : _achievements)
    {
        _mainLayer->removeChild(it->getGameButton());
    }
    _achievements.clear();
}

//
void ButtonLayer::resetAll()
{
    this->reset();
    // Reset controls
    for(auto it : _controls)
    {
        _mainLayer->removeChild(it->getGameButton());
    }
    _controls.clear();
}