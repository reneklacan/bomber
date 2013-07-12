#include "EffectButton.h"

using namespace Bomber::Frontend;

EffectButton::EffectButton(Rect imageRect, Texture2D *texture)
: _textWidth(20), _textHeight(20), _imageScale(0.8)
{
    Node *effectButton = new Node();

    Sprite *effectButtonImage = Sprite::createWithTexture(
        texture,
        imageRect
    );
    effectButtonImage->setAnchorPoint(ccp(0,0));

    LabelTTF* effectCounter = LabelTTF::create(
        "1",
        "Helvetica",
        32,
        CCSizeMake(_textWidth, _textHeight), 
        kTextAlignmentRight
    );
    effectCounter->enableStroke( ccc3(0, 0, 0), 10 );
    effectCounter->setPosition( ccp(
            effectButtonImage->getContentSize().width - _textWidth,
            20
        ) 
    );

    effectButton->setScale(_imageScale);

    effectButton->addChild(effectButtonImage, 1);
    effectButton->addChild(effectCounter, 1);

    _button = effectButton;
}