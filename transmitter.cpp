#include "transmitter.h"
#include "transmission.h"
#include <wiringPi.h>
#include <vector>

using namespace RFTools;

Transmitter::Transmitter(int pin) {
    this->pin = pin;
    pinMode(this->pin,OUTPUT);
}

Transmitter::~Transmitter() {
    pinMode(this->pin,INPUT);
}

void Transmitter::set(bool state) {
    if (state==true) {
        digitalWrite(this->pin,1);
    } else {
        digitalWrite(this->pin,0);
    }
}

bool Transmitter::get() {
    if (digitalRead(this->pin)==1) {
        return true;
    } else {
        return false;
    }
}

void Transmitter::transmit(const Transmission &t) {
    Transmission::const_iterator i;
    //set to off before transmission
    this->set(false);
    //transmit
    i = t.begin();
    while (i != t.end()) {
        this->set(i->state);
        delayMicroseconds(i->duration);
        i++;
    }
    //set to off at end of transmission
    this->set(false);
}
