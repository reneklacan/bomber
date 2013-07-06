#include "Main.h"
#include "../Classes/AppDelegate.h"
//#include "cocos2d.h"

#include "CCEGLView.h"

//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <string>

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // create the application instance
    AppDelegate app;

    EGLView* eglView = EGLView::sharedOpenGLView();
    eglView->setFrameSize(12*101, 12*81);

    return Application::sharedApplication()->run();
}
