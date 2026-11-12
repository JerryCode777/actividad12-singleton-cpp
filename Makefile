CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -pedantic

.PHONY: all run clean

all: singleton

singleton: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o singleton

run: singleton
	./singleton

clean:
	rm -f singleton
