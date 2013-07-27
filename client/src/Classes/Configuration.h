

#include "Constants.h"
#include "Gameplay/Macros.h"
#include "Input\Keyboard\Keyboard.h"

namespace Bomber
{
    namespace Intern
    {
        class BomberConfiguration
        {
            public:
                static BomberConfiguration *getInstance();

                BomberConfiguration();
                
                // player 1 keyboard configuration
                int kbPlayer1UpKey;
                int kbPlayer1DownKey;
                int kbPlayer1LeftKey;
                int kbPlayer1RightKey;

                int kbPlayer1BombKey;
                
                // player 2 keyboard configuration
                int kbPlayer2UpKey;
                int kbPlayer2DownKey;
                int kbPlayer2LeftKey;
                int kbPlayer2RightKey;

                int kbPlayer2BombKey;

            private:
                static BomberConfiguration *_instance;
        };
    }
}