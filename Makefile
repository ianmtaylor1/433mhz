CXX = g++-4.6
DEBUG = -g
OPTIMIZATION = -O1
INCDIRS = -I .
CFLAGS = -c -W -Wall -std=c++0x $(DEBUG) $(OPTIMIZATION) $(INCDIRS)
TESTDIR = tests
LFLAGS = -lwiringPi


all: lib bin test


# Executables and libraries ("end products")

codesend: codesend.o 433mhz.a
	$(CXX) -o $@ $^ $(LFLAGS)

433mhz.a: transmitter.o transmission.o txprotocols.o
	ar -cq $@ $^

# Tests

$(TESTDIR)/txtest: $(TESTDIR)/txtest.o transmitter.o transmission.o txprotocols.o
	$(CXX) -o $@ $^ $(LFLAGS)

# Object files

codesend.o: codesend.cpp 433mhz.h
	$(CXX) $(CFLAGS) -o $@ codesend.cpp

transmitter.o: transmitter.cpp transmitter.h transmission.h
	$(CXX) $(CFLAGS) -o $@ transmitter.cpp

txprotocols.o: txprotocols.cpp txprotocols.h transmission.h
	$(CXX) $(CFLAGS) -o $@ txprotocols.cpp

transmission.o: transmission.cpp transmission.h
	$(CXX) $(CFLAGS) -o $@ transmission.cpp

$(TESTDIR)/txtest.o: $(TESTDIR)/txtest.cpp txprotocols.h transmission.h transmitter.h
	$(CXX) $(CFLAGS) -o $@ $(TESTDIR)/txtest.cpp

# Header files

433mhz.h: transmission.h transmitter.h txprotocols.h

transmitter.h: transmission.h

txprotocols.h: transmission.h

# Dummy targets

lib: 433mhz.a

bin: codesend

tests: $(TESTDIR)/txtest

clean:
	-rm *.o
	-rm *.a
	-rm tests/*.o
	-rm tests/txtest
	-rm codesend
