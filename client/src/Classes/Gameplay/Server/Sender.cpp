/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Logic
 */

#include "Sender.h"

 //
void Sender::init()
{
    int x = 1;
    while(1) {
        std::cout << "Sender: " << x++ << std::endl;
        sleep(1);
    }
    return;
}