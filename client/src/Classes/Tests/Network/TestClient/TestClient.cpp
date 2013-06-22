
#include "../../../Network/Client/ClientConnection.h"
#include "../../../Network/Client/Client.h"

int main()
{
    //runClient2();
    //return 0;

    ClientConnection *cc = new ClientConnection("localhost", "8888");
    while (1)
    {
        std::cout << "tu\n";
        std::vector<unsigned char> msg;
        msg.push_back('x');
        msg.push_back('y');
        msg.push_back('z');
        cc->send(msg);
        //cc->send((char *) "abc");
        sleep(1);
    }

    return 0;
}
