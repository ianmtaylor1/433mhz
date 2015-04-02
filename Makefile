CXX = g++-4.6
DEBUG = -g
OPTIMIZATION = -O1
INCDIRS = -I .
CFLAGS = -c -W -Wall -std=c++0x $(DEBUG) $(OPTIMIZATION) $(INCDIRS)
TESTDIR = tests
LFLAGS = -lwiringPi

# Executables and libraries ("end products")

# Tests

$(TESTDIR)/txtest: $(TESTDIR)/txtest.o transmitter.o transmission.o txprotocols.o
	$(CXX) -o $@ $^ $(LFLAGS)

# Object files

transmitter.o: transmitter.cpp transmitter.h transmission.h
	$(CXX) $(CFLAGS) -o $@ transmitter.cpp

txprotocols.o: txprotocols.cpp txprotocols.h transmission.h
	$(CXX) $(CFLAGS) -o $@ txprotocols.cpp

transmission.o: transmission.cpp transmission.h
	$(CXX) $(CFLAGS) -o $@ transmission.cpp

$(TESTDIR)/txtest.o: $(TESTDIR)/txtest.cpp txprotocols.h transmission.h transmitter.h
	$(CXX) $(CFLAGS) -o $@ $(TESTDIR)/txtest.cpp

# Header files

transmitter.h: transmission.h

txprotocols.h: transmission.h

# Dummy targets

tests: $(TESTDIR)/txtest

clean:
	rm *.o
	rm tests/*.o
	rm tests/txtest
