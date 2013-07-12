#include "EffectButton.h"

using namespace Bomber::Frontend;

EffectButton::EffectButton(unsigned int id, Rect imageRect, Texture2D *texture)
: _id(id), _textWidth(40), _textHeight(20), _imageScale(0.8), _label(1)
{
    Node *effectButton = new Node();

    Sprite *effectButtonImage = Sprite::createWithTexture(
        texture,
        imageRect
    );
    effectButtonImage->setAnchorPoint(ccp(0,0));

    _effectCounter = LabelTTF::create(
        std::to_string(_label).c_str(),
        "Helvetica",
        32,
        CCSizeMake(_textWidth, _textHeight), 
        kTextAlignmentRight
    );
    _effectCounterStroke = LabelTTF::create(
        std::to_string(_label).c_str(),
        "Helvetica",
        36,
        CCSizeMake(_textWidth, _textHeight), 
        kTextAlignmentRight
    );

    _effectCounter->setPosition( ccp(
            effectButtonImage->getContentSize().width - _textWidth/1.3,
            _textHeight
        ) 
    );
    _effectCounterStroke->setPosition( ccp(
            effectButtonImage->getContentSize().width - _textWidth/1.3 - 2,
            _textHeight - 1
        ) 
    );
    _effectCounterStroke->setColor( ccc3(0,0,0) );

    effectButton->setScale(_imageScale);

    effectButton->addChild(effectButtonImage, 1);
    effectButton->addChild(_effectCounterStroke, 1);
    effectButton->addChild(_effectCounter, 1);

    _button = effectButton;
}

void EffectButton::incrementLabel()
{
    _label++;
    _effectCounter->setString( std::to_string(_label).c_str() );
    _effectCounterStroke->setString( std::to_string(_label).c_str() );
}