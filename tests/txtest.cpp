/* Tests the transmitter code to send codes for one of my outlets. */

#include "transmission.h"
#include "transmitter.h"
#include "txprotocols.h"
#include <unistd.h>
#include <iostream>
#include <wiringPi.h>

using RFTools::protocol1;
using RFTools::tristate;
using RFTools::Transmitter;
using RFTools::Transmission;

int main(int argc, char **argv)
{
    Transmission on  = protocol1(1144067,24,186);
    Transmission off = protocol1(1144076,24,186);
    
    Transmission t_on  = tristate("0F0FF1FF0001",186);
    Transmission t_off = tristate("0F0FF1FF0010",186);
    
    Transmission test_on  = tristate("0F0FFFFF0001",186);
    Transmission test_off = tristate("0F0FFFFF0010",186);
    
    //don't need these
    (void) argc;
    (void) argv;
    
    wiringPiSetup();
    
    Transmitter tx = Transmitter(0);
    
    for (int i=0; i<3; i++) {
        tx.transmit(on);
        sleep(1);
        tx.transmit(off);
        sleep(1);
    }
    for (int i=0; i<3; i++) {
        tx.transmit(t_on);
        sleep(1);
        tx.transmit(t_off);
        sleep(1);
    }
    for (int i=0; i<3; i++) {
        tx.transmit(test_on);
        sleep(1);
        tx.transmit(test_off);
        sleep(1);
    }

    return 0;
}
