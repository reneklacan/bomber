#include "../Classes/AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

class Params
{
    public:
        Params(int argc, char **argv)
        {
            _level = nullptr;

            for (int i = 1; i < argc - 1; i++)
            {
                if (strcmp(argv[i], "--level") == 0 || strcmp(argv[i], "-l"))
                {
                    _level = argv[i + 1];
                    i++;
                }
            }
        }
        char *getLevel() { return _level; }

    private:
        char *_level;
};

int main(int argc, char **argv)
{
    auto params = Params(argc, argv);

    // create the application instance
    AppDelegate app(params.getLevel());

    EGLView* eglView = EGLView::sharedOpenGLView();
    eglView->setFrameSize(1350, 750);

    return Application::sharedApplication()->run();
}
