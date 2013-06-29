#include "GameButton.h"

using namespace Bomber::Frontend;

//
GameButton *GameButton::createButton(CCObject* target, SEL_MenuHandler handler)
{
    CCMenu* pMenu = NULL;
    do {
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            target,
            handler
        );

        CC_BREAK_IF(! pCloseItem);
        
        // Set Button position
        GameButton::addButton(
            (GameButton *)pMenu,
            pCloseItem->getContentSize().width,
            pCloseItem->getContentSize().height
        );

        pCloseItem->setPosition(_buttons[_buttonsOrder.back()]);

        // Add Button, it is an auto release object.
        pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
    } while(0);

    return (GameButton *)pMenu;
}

//
void GameButton::addButton(GameButton *button, unsigned int width, unsigned int height)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCPoint last = ccp(origin.x + visibleSize.width, origin.y + visibleSize.height);
    if(GameButton::_buttonsOrder.size() > 0)
    {
        last = _buttons[_buttonsOrder.back()];
    }
    CCPoint next;
    next.x = last.x - width;
    next.y = origin.y + visibleSize.height - height;
    // TODO: second line  

    _buttonsOrder.push_back(button);
    _buttons[button] = next;
}