/* Tests the transmitter code to send codes for one of my outlets. */

#include "transmission.h"
#include "transmitter.h"
#include "txprotocols.h"
#include <unistd.h>
#include <iostream>
#include <wiringPi.h>

using RFTools::protocol1;
using RFTools::Transmitter;
using RFTools::Transmission;

int main(int argc, char **argv)
{
    Transmission on = protocol1(1144067,24,186);
    Transmission off = protocol1(1144076,24,186);
    
    //std::cout << on.size() << "\n";
    //std::cout << off.size() << "\n";
    
    wiringPiSetup();
    
    Transmitter tx = Transmitter(0);
    
    for (int i=0; i<10; i++) {
        tx.transmit(on);
        sleep(1);
        tx.transmit(off);
        sleep(1);
    }

    return 0;
}
