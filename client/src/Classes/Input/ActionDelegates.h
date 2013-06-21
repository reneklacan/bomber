#ifndef __ACTION_DELEGATES
#define __ACTION_DELEGATES

class PauseGameDelegate
{
    public:
        virtual void pauseGameAction() = 0;
};

class GameActionDelegate
{
    public:
        virtual void actionOne() = 0;
        virtual void actionTwo() = 0;
        virtual void actionThree() = 0;
};

#endif

