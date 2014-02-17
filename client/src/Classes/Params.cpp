
#include <cstring>

#include "Params.h"

using namespace std;

vector<string> split(string text, string delimeter)
{
    vector<string> result;
    string substring;
    int delimPos;

    while (1)
    {
        delimPos = text.find_first_of(delimeter);

        if (delimPos < 0)
        {
            if (text.compare("") != 0)
                result.push_back(text);

            break;
        }
        else
        {
            substring = text.substr(0, delimPos);

            if (substring.compare("") != 0)
                result.push_back(substring);

            text = text.substr(delimPos + 1); 
        }
    }

    return result;
}

vector<string> split(char *text, string delimeter)
{
    string textString(text);
    return split(textString, delimeter);
}

Params::Params(int argc, char **argv)
{
    _level = nullptr;

    for (int i = 0; i < argc - 1; i++)
    {
        if (strcmp(argv[i], "--level") == 0 || strcmp(argv[i], "-l") == 0)
        {
            _level = argv[i + 1];
            strcpy(_level, split(_level, "/").back().c_str());
            strcpy(_level, split(_level, "\\").back().c_str());
            i++;
        }
    }
}


