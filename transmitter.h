#ifndef _transmitter_h
#define _transmitter_h

#include <wiringPi.h>
#include <vector>

#include "transmission.h"

namespace RFTools {

/* Class that is a transmitter for a simple OOK RF chip on the Raspberry Pi 
 * This class works on Raw timings: i.e. toggles the transmitter, waits
 * a number of microseconds and repeats. Other functions and classes must
 * translate codes into these timings. */
class Transmitter {

  public:
    Transmitter(int pin);
    ~Transmitter();
 
    void set(bool state);
    bool get();
    
    void transmit(const Transmission &t);

  private:
    int pin;

};

};

#endif //ifndef _transmitter_h
