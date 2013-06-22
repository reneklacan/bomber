
#include "../../../Network/Client/ClientConnection.h"
#include "../../../Network/Client/Client.h"

class TestReceiver : public ReceiveDelegate
{
    public:
        void receiveData(const char* msg)
        {
            std::cout << "receive in delegate: " << msg << "\n";
        }
};


int main()
{
    ClientConnection *cc = new ClientConnection("localhost", "8888");
    TestReceiver *receiver = new TestReceiver();
    cc->addReceiveDelegate(receiver);

    while (1)
    {
        std::cout << ".\n";
        cc->send((char *) "abcpol");
        sleep(1);
    }

    return 0;
}
