#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include <tclap/CmdLine.h>
#include <wiringPi.h>

#include "433mhz.h"


int main(int argc, const char *argv[])
{
    //construct the command line parser
    TCLAP::CmdLine cmd("Sends a code on the 433mhz transmitter.",' ',"0.0");
    TCLAP::ValueArg<int> pinArg("p","txpin","GPIO pin number used to transmit (wiringPi)",true,0,"integer",cmd);
    TCLAP::ValueArg<unsigned int> pulselengthArg("l","pulselength","Time in microseconds of the shortest pulse",true,200,"integer",cmd);
    TCLAP::ValueArg<int> repeatArg("r","repeat","Number of times to repeat the transmission",true,10,"integer",cmd);
    std::vector<std::string> protocols;
    protocols.push_back("tristate");
    protocols.push_back("protocol1");
    protocols.push_back("protocol2");
    TCLAP::ValuesConstraint<std::string> proto_con (protocols);
    TCLAP::ValueArg<std::string> protocolArg("t","protocol","Protocol to use sending the code",true,"tristate",&proto_con,cmd);
    TCLAP::UnlabeledMultiArg<std::string> codeArg("code","Code to send",true,"string/integer",cmd);
    //get the arguments
    cmd.parse(argc,argv);
    unsigned int pulselength = pulselengthArg.getValue();
    int pin = pinArg.getValue();
    int repeat = repeatArg.getValue();
    std::string protocol = protocolArg.getValue();
    std::vector<std::string> codevec = codeArg.getValue();
    //set up wiringPi and Transmitter
    wiringPiSetup();
    RFTools::Transmitter tx (pin);
    //prepare and transmit the code
    if (protocol=="tristate") {
        if (codevec.size() > 1) {
            std::cout << "tristate only requires one codeword" << std::endl;
            return 1;
        }
        RFTools::Transmission code = RFTools::tristate(codevec[0],pulselength,repeat);
        tx.transmit(code);
    } else if (protocol=="protocol1") {
        std::cout << protocol << " not implemented." << std::endl;
        return 2;
    } else if (protocol=="protocol2") {
        std::cout << protocol << " not implemented." << std::endl;
        return 2;
    } else {
        std::cout << "Unknown protocol " << protocol << std::endl;
        return 1;
    }
    return 0;
}

