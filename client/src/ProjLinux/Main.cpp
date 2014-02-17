#include "../Classes/Params.h"
#include "../Classes/AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
    auto params = Params(argc, argv);

    printf("level = %s\n", params.getLevel());

    // create the application instance
    AppDelegate app(params.getLevel());

    EGLView* eglView = EGLView::sharedOpenGLView();
    eglView->setFrameSize(1350, 750);

    return Application::sharedApplication()->run();
}
