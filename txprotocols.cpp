#include <vector>
#include <bitset>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include "txprotocols.h"
#include "transmission.h"

using namespace RFTools;

/* Type that defines different bits for different transmissions.
   Allows us to combine a lot of code */
typedef std::unordered_map<char, Transmission> TXBitMap;

/* Functions to construct/return the protocolmap for the different protocols.
   Since it's difficult/impossible to construct complex classes as global
   variables, we'll use a function with a static variable contained. */
const TXBitMap& protocol1_map();
const TXBitMap& protocol2_map();
const TXBitMap& tristate_map();

/* generic_create
   Creates a transmission based on a raw string code and a map translating
   that code into pulses. All pulses are multiplied by pulselength.
   Note that this function does not repeat or add sync bits. All of that
   should be taken care of by the calling function. This function's sole 
   sole purpose is to be a generic way to use the TXBitMaps for handling
   different protocols.
 */
Transmission generic_create(std::string code, unsigned int pulselength, 
                            const TXBitMap& proto_map);

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
    std::string totalcode("");
    //repeat that vector nrepeat times
    for (int i=0; i<nrepeat; i++) {
        totalcode += code + 'S';
    }
    return generic_create(totalcode,pulselength,protocol1_map());
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
    std::string totalcode("");
    //repeat that vector nrepeat times
    for (int i=0; i<nrepeat; i++) {
        totalcode += code + 'S';
    }
    return generic_create(totalcode,pulselength,protocol2_map());
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
                       unsigned int pulselength, int nrepeat/*=10*/)
{
    //stubbed
    return Transmission();
}

Transmission RFTools::codewordB(int addresscode, int channelcode, bool status, 
                       unsigned int pulselength, int nrepeat/*=10*/)
{
    //stubbed
    return Transmission();
}

Transmission RFTools::codewordC(char family, int group, int device, bool status,
                       unsigned int pulselength, int nrepeat/*=10*/)
{
    //stubbed
    return Transmission();
}

Transmission RFTools::tristate(std::string code, unsigned int pulselength, int nrepeat/*=10*/)
{
    std::string totalcode("");
    //repeat that vector nrepeat times
    for (int i=0; i<nrepeat; i++) {
        totalcode += code + 'S';
    }
    return generic_create(totalcode,pulselength,tristate_map());
}

/********************** FUNCTIONS NOT IN HEADER **************************
 ****************** FOR INTERNAL USE IN THE MODULE ***********************/

Transmission generic_create(std::string code, unsigned int pulselength, 
                            const TXBitMap& proto_map)
{
    Transmission final;
    //go through the code and append to the transmission
    for (unsigned int b=0; b<code.length(); b++) {\
        //could throw exception!
        Transmission to_append;
        try {
            to_append = proto_map.at(code[b]);
        } catch (const std::out_of_range& oor) {
            throw TXProtoException("Unknown character in code string.");
        }
        for (unsigned int x=0; x<to_append.size(); x++) {
            // uses the multiplication operator of RFTools::Signal
            final.push_back(to_append[x]*pulselength);
        }
    }
    return final;
}


const TXBitMap& protocol1_map()
{
    static bool created = false;
    static TXBitMap map;
    //if we've already created it, return it
    if (!created) {
        Transmission zero;
        Transmission one;
        Transmission sync;
        zero.push_back(Signal(true,1));
        zero.push_back(Signal(false,3));
        one.push_back(Signal(true,3));
        one.push_back(Signal(false,1));
        sync.push_back(Signal(true,1));
        sync.push_back(Signal(false,31));
        map['0'] = zero;
        map['1'] = one;
        map['S'] = sync;
        created = true;
    }
    return map;
}

const TXBitMap& protocol2_map()
{
    static bool created = false;
    static TXBitMap map;
    //if we've already created it, return it
    if (!created) {
        Transmission zero;
        Transmission one;
        Transmission sync;
        zero.push_back(Signal(true,1));
        zero.push_back(Signal(false,2));
        one.push_back(Signal(true,2));
        one.push_back(Signal(false,1));
        sync.push_back(Signal(true,1));
        sync.push_back(Signal(false,10));
        map['0'] = zero;
        map['1'] = one;
        map['S'] = sync;
        created = true;
    }
    return map;
}

const TXBitMap& tristate_map()
{
    static bool created = false;
    static TXBitMap map;
    //if we've already created it, return it
    if (!created) {
        Transmission zero;
        Transmission one;
        Transmission f;
        Transmission sync;
        zero.push_back(Signal(true,1));
        zero.push_back(Signal(false,3));
        zero.push_back(Signal(true,1));
        zero.push_back(Signal(false,3));
        one.push_back(Signal(true,3));
        one.push_back(Signal(false,1));
        one.push_back(Signal(true,3));
        one.push_back(Signal(false,1));
        f.push_back(Signal(true,1));
        f.push_back(Signal(false,3));
        f.push_back(Signal(true,3));
        f.push_back(Signal(false,1));
        sync.push_back(Signal(true,1));
        sync.push_back(Signal(false,31));
        map['0'] = zero;
        map['1'] = one;
        map['S'] = sync;
        map['F'] = f;
        created = true;
    }
    return map;
}
