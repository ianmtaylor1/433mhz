#include <vector>
#include <bitset>
#include <string>
#include "txprotocols.h"
#include "transmission.h"

using namespace RFTools;


/* Protocol based on protocol 1 from the ninjablocks code.
   Bits are translated to pulses as follows (H = TX on, L = TX off)
   0    = HLLL
   1    = HHHL
   Sync = HLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
   Each pulse (either H or L) is pulselength microseconds long.
   The code is sent code is sent as a string of bits bitlength long, and
   repeated nrepeat times with a Sync bit after each time.
*/
Transmission RFTools::protocol1(unsigned long long code, int bitlength, unsigned int pulselength, int nrepeat/*=10*/)
{
    //check for correct parameters
    if (code > 1ull<<(bitlength-1)) {
        throw TXProtoException("Code too large for specified bitlength.");
    } else if (bitlength > 128) {
        throw TXProtoException("Bit length can be at most 128.");
    }
    //create the codestring as the last digits of a bitset based on the code
    std::string codestring (std::bitset<128>(code).to_string(),128-bitlength);
    return protocol1(codestring,pulselength,nrepeat);
}

Transmission RFTools::protocol1(std::string code, unsigned int pulselength, int nrepeat/*=10*/)
{
    Transmission tx;
    Transmission codevec;
    //create vector based on code
    for (unsigned int b=0; b<code.length(); b++) {
        if (code[b]=='1') {
            codevec.push_back(Signal(true,3*pulselength));
            codevec.push_back(Signal(false,pulselength));
        } else if (code[b]=='0') {
            codevec.push_back(Signal(true,pulselength));
            codevec.push_back(Signal(false,3*pulselength));
        } else {
            throw TXProtoException("Unknown character in code string.");
        }
    }
    //repeat that vector nrepeat times
    for (int i=0; i<nrepeat; i++) {
        //send code
        tx.insert(tx.end(),codevec.begin(),codevec.end());
        //add sync
        tx.push_back(Signal(true,pulselength));
        tx.push_back(Signal(false,31*pulselength));
    }
    return tx;
}


/* Protocol based on protocol 2 from the ninjablocks code.
   Bits are translated to pulses as follows (H = TX on, L = TX off)
   0    = HLL
   1    = HHL
   Sync = HLLLLLLLLLL
   Each pulse (either H or L) is pulselength microseconds long.
   The code is sent code is sent as a string of bits bitlength long, and
   repeated nrepeat times with a Sync bit after each time.
*/
Transmission RFTools::protocol2(unsigned long long code, int bitlength, unsigned int pulselength, int nrepeat/*=10*/)
{
    //check for correct parameters
    if (code > 1ull<<(bitlength-1)) {
        throw TXProtoException("Code too large for specified bitlength.");
    } else if (bitlength > 128) {
        throw TXProtoException("Bit length can be at most 128.");
    }
    //create codestring as last digits of bitset based on code
    std::string codestring (std::bitset<128>(code).to_string(),128-bitlength);
    return protocol2(codestring,pulselength,nrepeat);
}

Transmission RFTools::protocol2(std::string code, unsigned int pulselength, int nrepeat/*=10*/)
{
    Transmission tx;
    Transmission codevec;
    //create vector based on code
    for (unsigned int b=0; b<code.length(); b++) {
        if (code[b]=='1') {
            codevec.push_back(Signal(true,2*pulselength));
            codevec.push_back(Signal(false,pulselength));
        } else if (code[b]=='0') {
            codevec.push_back(Signal(true,pulselength));
            codevec.push_back(Signal(false,2*pulselength));
        } else {
            throw TXProtoException("Unknown character in code string.");
        }
    }
    //repeat that vector nrepeat times
    for (int i=0; i<nrepeat; i++) {
        //send code
        tx.insert(tx.end(),codevec.begin(),codevec.end());
        //add sync
        tx.push_back(Signal(true,pulselength));
        tx.push_back(Signal(false,10*pulselength));
    }
    return tx;
}


/* Protocols that work with "tristate" transmissions. The basis of each code
   is three characters: 0, 1, and F.
   0 = HLLLHLLL
   1 = HHHLHHHL
   F = HLLLHHHL
   Sync = HLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
   Each pulse (either H or L) is pulselength microseconds long.
   The code is sent as a string of bits bitlength long, and
   repeated nrepeat times with a Sync bit after each time.
*/
Transmission RFTools::codewordA(std::string group, int channelcode, bool status,
                       unsigned int pulselength, int nrepeat=10)
{
    //stubbed
    return Transmission();
}

Transmission RFTools::codewordB(int addresscode, int channelcode, bool status, 
                       unsigned int pulselength, int nrepeat=10)
{
    //stubbed
    return Transmission();
}

Transmission RFTools::codewordC(char family, int group, int device, bool status,
                       unsigned int pulselength, int nrepeat=10)
{
    //stubbed
    return Transmission();
}

Transmission RFTools::tristate(std::string code, unsigned int pulselength, int nrepeat/*=10*/)
{
    Transmission tx;
    Transmission codevec;
    //create vector based on code
    for (unsigned int b=0; b<code.length(); b++) {
        if (code[b]=='1') {
            codevec.push_back(Signal(true,3*pulselength));
            codevec.push_back(Signal(false,pulselength));
            codevec.push_back(Signal(true,3*pulselength));
            codevec.push_back(Signal(false,pulselength));
        } else if (code[b]=='0') {
            codevec.push_back(Signal(true,pulselength));
            codevec.push_back(Signal(false,3*pulselength));
            codevec.push_back(Signal(true,pulselength));
            codevec.push_back(Signal(false,3*pulselength));
        } else if (code[b]=='F') {
            codevec.push_back(Signal(true,pulselength));
            codevec.push_back(Signal(false,3*pulselength));
            codevec.push_back(Signal(true,3*pulselength));
            codevec.push_back(Signal(false,pulselength));
        } else {
            throw TXProtoException("Unknown character in code string.");
        }
    }
    //repeat that vector nrepeat times
    for (int i=0; i<nrepeat; i++) {
        //send code
        tx.insert(tx.end(),codevec.begin(),codevec.end());
        //add sync
        tx.push_back(Signal(true,pulselength));
        tx.push_back(Signal(false,31*pulselength));
    }
    return tx;
}
