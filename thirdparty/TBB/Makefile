SOURCE = $(wildcard *.cpp)
UT = $(subst test_,,$(patsubst %.cpp,%,$(SOURCE)))
ROOT=~/source/tbb
#LIB_DIR=$(ROOT)/build/linux_intel64_gcc_cc4.8.5_libc2.17_kernel3.10.0_release/
##build/lib is a symbol link
LIB_DIR=$(ROOT)/build/lib
HEADER = $(ROOT)/include
SO = libkids.so
CC = g++
CFLAGS = -std=c++11 -pthread -Werror=return-type -ldl

ALL: $(UT) $(LIB)

%: test_%.cpp
	$(CC) $(CFLAGS) -I $(HEADER) -L $(LIB_DIR) -ltbb $< -Wl,-rpath $(LIB_DIR) -o $@

.PHONY: clean love
clean:
	rm -rf *.out *.o *.so *.lib $(UT) core.*
love:
	$(MAKE) clean && $(MAKE)
