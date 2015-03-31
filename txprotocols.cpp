#include <vector>
#include <bitset>
#include <string>
#include "txprotocols.h"
#include "transmission.h"

using namespace RFTools;

Transmission RFTools::protocol1(unsigned long long code, int bitlength, unsigned int pulselength, int nrepeat/*=10*/)
{
    //initialize bitset to code value
    if (code > 1ull<<(bitlength-1)) {
        throw TXProtoException("Code too large for specified bitlength.");
    } else if (bitlength > 128) {
        throw TXProtoException("Bit length can be at most 128.");
    }
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


Transmission RFTools::protocol2(unsigned long long code, int bitlength, unsigned int pulselength, int nrepeat/*=10*/)
{
    //initialize bitset to code value
    if (code > 1ull<<(bitlength-1)) {
        throw TXProtoException("Code too large for specified bitlength.");
    } else if (bitlength > 128) {
        throw TXProtoException("Bit length can be at most 128.");
    }
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

