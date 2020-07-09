SOURCE = $(wildcard *.cpp)
BIN = $(patsubst %.cpp, %.out,$(SOURCE))
CC = g++
CFLAGS = -std=c++11 -lfaiss -lomp

ALL: $(BIN)

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean love
clean:
	rm -rf *.out *.o *.so *.lib $(BIN) core.*
love:
	$(MAKE) clean && $(MAKE)
