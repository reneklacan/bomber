#ifndef __BOMBER_FRONTEND_PRIM_COLLISION_AREA
#define __BOMBER_FRONTEND_PRIM_COLLISION_AREA

#include "cocos2d.h"

using namespace cocos2d;

namespace Bomber
{
    namespace Frontend
    {
        class CollisionArea
        {
        public:
        	void setPoint(Point point) { _point = point; }
        	void setPlayersID(std::vector<unsigned int> ids) { _playersID = ids; }
        	float getX() { return _point.x; }
        	float getY() { return _point.y; }

        	void removePlayer(unsigned int id)
        	{
        		bool found = false;
        		int counter = 0;
        		for(auto playerID : _playersID)
        		{
        			if(playerID == id)
        			{
        				found = true;
        				break;
        			}
        			counter++;
        		}
        		if(found)
        		{
        			_playersID.erase(_playersID.begin() + counter);
        		}
        	}

        	bool isEmpty()
        	{
        		if(_playersID.size() == 0)
        		{
        			return true;
        		}
        		return false;
        	}

        	bool playerInArea(unsigned int id)
        	{
        		for(auto playerID : _playersID)
        		{
        			if(playerID == id)
        			{
        				return true;
        			}
        		}
        		return false;
        	}

        private:
        	Point _point;
        	std::vector<unsigned int> _playersID;
        };
    }
}
#endif