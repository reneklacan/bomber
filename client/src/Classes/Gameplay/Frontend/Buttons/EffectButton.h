#ifndef __BOMBER_FRONTEND_EFFECTBUTTON
#define __BOMBER_FRONTEND_EFFECTBUTTON

#include "cocos2d.h"
#include "GameButton.h"

namespace Bomber
{
    namespace Frontend
    {
        class EffectButton : public GameButton
        {
        public:
            EffectButton(unsigned int id, Rect imageRect, Texture2D *texture);
            unsigned int getID() { return _id; }
            void incrementLabel();

        private:
            unsigned int _id;
            unsigned int _textWidth;
            unsigned int _textHeight;
            float _imageScale;
            LabelTTF* _effectCounter;
            LabelTTF* _effectCounterStroke;
            unsigned int _label;

        };

    }
}

#endif