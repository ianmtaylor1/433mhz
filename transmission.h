/* Class that represents a sent/received transmission through
   the transmitter/receiver */

#ifndef _transmission_h
#define _transmission_h

#include <vector>

namespace RFTools {

/* Struct to represent a single signal in a series (or transmission)
 * Represents the given state lasting for the given number of microseconds.
*/
struct Signal {
    Signal(bool state, unsigned int duration) : 
        state(state), duration(duration)
        {};
    bool state;
    unsigned int duration;
};

/* A transmission is represented as a vector of Signals */
typedef std::vector<Signal> Transmission;

/* condense
 * "condenses" the given transmission by combining adjacent signals with the
 * same state. Operates in place, and returns a reference to the same argument
 * (for ease of use in chained function calls)
*/
Transmission & condense(Transmission &t);

};

#endif //ifndef _transmission_h
