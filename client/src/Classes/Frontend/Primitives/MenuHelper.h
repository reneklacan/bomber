#ifndef __BOMBER_FRONTEND_PRIM_MENU
#define __BOMBER_FRONTEND_PRIM_MENU

#include "cocos2d.h"
#include <string>
#include "../../Common/Primitives/ConnectionType.h"

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
                void setLevelFilename(std::string filename) { _levelFilename = filename; }
                void setNumPlayers(unsigned int num) { _players = num; }
                void setConnection(Bomber::Common::TConnectionType con) { _connection = con; }
                std::string getLevelName() { return _levelName; }
                std::string getLevelFilename() { return _levelFilename; }
                unsigned int getNumPlayers() {return _players; }
                Bomber::Common::TConnectionType getConnection() {return _connection; }


            private:
                MenuSelections()
                :_levelName("")
                ,_levelFilename("")
                ,_players(1)
                ,_connection(Bomber::Common::NONE_CON)
                {}

                std::string _levelName;
                std::string _levelFilename;
                unsigned int _players;
                Bomber::Common::TConnectionType _connection;
        };
    }
}

#endif
