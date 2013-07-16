#ifndef __BOMBER_FRONTEND_SPRITE_CREATOR
#define __BOMBER_FRONTEND_SPRITE_CREATOR

#include "cocos2d.h"

#include "../../../Input/ControlLayer.h"

namespace Bomber
{
    namespace Frontend
    {
    	class SpriteCreator
    	{
    	public:
            static SpriteCreator *getInstance();

            Sprite* createObstacle();
            Sprite* createSprite();
            Sprite* createEffect(Texture2D *texture, Rect rect);
            Sprite* createBomb();

        private:
        	SpriteCreator() {}

    	};
	}

}

#endif