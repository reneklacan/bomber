#include "io.h"
#include "fcntl.h"

#include "Main.h"
#include "../Classes/Params.h"
#include "../Classes/AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

#define BOMBER_MAIN_DEBUG 1

static void openConsole()
{
    int outHandle, errHandle, inHandle;
    FILE *outFile, *errFile, *inFile;
    AllocConsole();
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = 9999;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

    outHandle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    errHandle = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE),_O_TEXT);
    inHandle = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE),_O_TEXT );

    outFile = _fdopen(outHandle, "w" );
    errFile = _fdopen(errHandle, "w");
    inFile =  _fdopen(inHandle, "r");

    *stdout = *outFile;
    *stderr = *errFile;
    *stdin = *inFile;

    setvbuf( stdout, NULL, _IONBF, 0 );
    setvbuf( stderr, NULL, _IONBF, 0 );
    setvbuf( stdin, NULL, _IONBF, 0 );

    std::ios::sync_with_stdio();
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#if BOMBER_MAIN_DEBUG > 0
    openConsole();
#endif
	printf("hovno\n");
	auto params = Params(__argc, __argv);
	printf("hovno\n");

	printf("level = %s\n", params.getLevel());

    AppDelegate app(params.getLevel());

    EGLView* eglView = EGLView::sharedOpenGLView();
    eglView->setFrameSize(1350, 750);

    return Application::sharedApplication()->run();
}