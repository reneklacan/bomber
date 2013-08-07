#ifndef __BOMBER_FRONTEND_PRIM_MENU
#define __BOMBER_FRONTEND_PRIM_MENU

#include "cocos2d.h"

#include <string>

using namespace cocos2d;

namespace Bomber
{
    namespace Frontend
    {
        class MenuSelections
        {
        public:
        	static MenuSelections *getInstance()
			{
			    static MenuSelections instance;
			    return &instance;
			}
			void setLevelName(std::string name) { _levelName = name; }
			void setNumPlayers(unsigned int num) { _players = num; }
			std::string getLevelName() { return _levelName; }
			unsigned int getNumPlayers() {return _players; }


        private:
        	MenuSelections()
        	: _levelName(""), _players(1) {}

        	std::string _levelName;
        	unsigned int _players;
        };
    }
}

#endif