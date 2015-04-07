#include <iostream>
#include <string>
#include <unistd.h>

#include <tclap/CmdLine.h>

#include "433mhz.h"


int main(int argc, const char *argv[])
{
    //construct the command line parser
    TCLAP::CmdLine cmd("Sends a code on the 433mhz transmitter.",' ',"0.0");
    int pulselength;
    std::string code;
    int repeat;
    cmd.parse(argc, argv);
    return 0;
}

