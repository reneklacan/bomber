#ifndef  BOMBER_PARAMS
#define  BOMBER_PARAMS

#include <string>
#include <vector>

std::vector<std::string> split(std::string text, std::string delimeter);
std::vector<std::string> split(char *text, std::string delimeter);

class Params
{
    public:
        Params(int argc, char **argv);
        char *getLevel() { return _level; }

    private:
        char *_level;
};

#endif
