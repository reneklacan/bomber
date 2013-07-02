#include "ControlButton.h"

using namespace Bomber::Frontend;

ControlButton::ControlButton(unsigned int id, std::string image, CCObject* target, SEL_MenuHandler handler)
{
    _id = id;
    _image = image;
    _target = target;
    _handler = handler;
    _button = NULL;
    do 
    {
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            image.c_str(),
            image.c_str(),
            target,
            handler
        );
        CC_BREAK_IF(! pCloseItem);
        
        // Set instance variables
        _width = pCloseItem->getContentSize().width;
        _height = pCloseItem->getContentSize().height;

        // Set initial position
        pCloseItem->setPosition( ccp(0, 0) );

        // Add Control button, it is an auto release object.
        _button = CCMenu::create(pCloseItem, NULL);
        _button->setPosition(CCPointZero);
        CC_BREAK_IF(! _button);
    }
    while(0);
}