SRC = $(wildcard *cpp)
BINS = $(patsubst %.cpp, %.out, $(SRC))

ALL: $(BINS)
	@echo $^

%.out: %.cpp
	g++ $^ -o $@ -I ~/local/include -std=c++11 -L ~/local/lib -lbenchmark -pthread -O2

clean:
	rm -rf *.out
