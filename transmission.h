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
    Signal(const Signal& other) : 
        state(other.state), duration(other.duration)
        {};

    Signal& operator=(const Signal& other)
    {
        if (this != &other) {
            this->state = other.state;
            this->duration = other.duration;
        }
        return *this;
    }
    /* Multiplication operators allow scaling by integers.
       Very handy for making all signals in a transmission multiples of a
       given pulselength */
    Signal& operator*=(unsigned int mult)
    {
        this->duration *= mult;
        return *this;
    }
    Signal operator*(unsigned int mult) const
    {
        return Signal(this->state, this->duration*mult);
    }

    bool state;
    unsigned int duration;
};
/* Allow multiplication with operands reversed */
Signal operator*(unsigned int mult, const Signal& s);

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
