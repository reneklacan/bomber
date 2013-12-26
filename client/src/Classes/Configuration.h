

#include "Constants.h"
#include "Macros.h"
#include "Input/Keyboard/Keyboard.h"

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
                
                int kbPlayer1UpKeyAlt;
                int kbPlayer1DownKeyAlt;
                int kbPlayer1LeftKeyAlt;
                int kbPlayer1RightKeyAlt;

                int kbPlayer1BombKeyAlt;
                
                // player 2 keyboard configuration
                int kbPlayer2UpKey;
                int kbPlayer2DownKey;
                int kbPlayer2LeftKey;
                int kbPlayer2RightKey;

                int kbPlayer2BombKey;

                int kbPlayer2UpKeyAlt;
                int kbPlayer2DownKeyAlt;
                int kbPlayer2LeftKeyAlt;
                int kbPlayer2RightKeyAlt;

                int kbPlayer2BombKeyAlt;

            private:
                static BomberConfiguration *_instance;
        };
    }
}
