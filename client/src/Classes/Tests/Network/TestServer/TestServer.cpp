
#include "../../../Network/Server/ServerConnection.h"
#include "../../../Network/Server/ReceiveDelegate.h"

class TestReceiver : public ReceiveDelegate
{
    public:
        void receiveServerData(const char* msg)
        {
            std::cout << "receive in delegate: " << msg << "\n";
        }
};

int main()
{
    ServerConnection *sc = new ServerConnection(8888);
    TestReceiver *receiver = new TestReceiver();
    sc->addReceiveDelegate(receiver);

    while (1)
    {
        std::cout << "tu\n";
        sc->dispatch((char *) "abcdefgh");
        sleep(2);
    }

    return 0;
}
