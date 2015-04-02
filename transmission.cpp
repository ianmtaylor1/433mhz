#include "transmission.h"

RFTools::Transmission & RFTools::condense(RFTools::Transmission &t)
{
    //STUBBED
    return t;
}


RFTools::Signal operator*(unsigned int mult, const RFTools::Signal& s)
{
    return s*mult;
}

