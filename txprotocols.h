/*
Functions that use various protocols to translate codes into timings for the 
Transmitter class. Each function might not take the same parameters as others
(e.g. some may take strings and some may take ints)
*/

#ifndef _txprotocols_h
#define _txprotocols_h

#include <vector>
#include <string>
#include <exception>
#include <stdio.h>

#include "transmission.h"

namespace RFTools {

/* Exception thrown by tx protocols */
class TXProtoException : public std::exception
{
  public:
    TXProtoException(const char *msg)
    {
        snprintf(this->msg,80,"%s",msg);
    }
    virtual const char* what() const throw()
    {
        return this->msg;
    }
  private:
    char msg[80];
};

/* Protocol based on protocol 1 from the ninjablocks code.
   Bits are translated to pulses as follows (H = TX on, L = TX off)
   0    = HLLL
   1    = HHHL
   Sync = HLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
   Each pulse (either H or L) is pulselength microseconds long.
   The code is sent code is sent as a string of bits bitlength long, and
   repeated nrepeat times with a Sync bit after each time.
*/
Transmission protocol1(unsigned long long code, int bitlength, unsigned int pulselength, int nrepeat=10);
Transmission protocol1(std::string code, unsigned int pulselength, int nrepeat=10);

/* Protocol based on protocol 2 from the ninjablocks code.
   Bits are translated to pulses as follows (H = TX on, L = TX off)
   0    = HLL
   1    = HHL
   Sync = HLLLLLLLLLL
   Each pulse (either H or L) is pulselength microseconds long.
   The code is sent code is sent as a string of bits bitlength long, and
   repeated nrepeat times with a Sync bit after each time.
*/
Transmission protocol2(unsigned long long code, int bitlength, unsigned int pulselength, int nrepeat=10);
Transmission protocol2(std::string code, unsigned int pulselength, int nrepeat=10);

Transmission tristate(std::string code, unsigned int pulselength, int nrepeat=10);

};

#endif //ifndef _protocols_h
