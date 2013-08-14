#ifndef __BOMBER_MIDDEND_NETCLIENT
#define __BOMBER_MIDDEND_NETCLIENT

namespace Bomber
{
    namespace Middend
    {
        class NetClient
        {
        public:
        	NetClient();
        	
        	bool isRunning() { return _running; }

        private:
        	bool _running;
        };
    }
}

#endif