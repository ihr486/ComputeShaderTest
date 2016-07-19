CXXSRCS := $(wildcard *.cpp)
CXXOBJS := $(CXXSRCS:%.cpp=%.o)
OBJS := $(CXXOBJS)

BIN := cstest

CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -O2 $(shell pkg-config --cflags sdl2 glew)
LDFLAGS := $(shell pkg-config --libs sdl2 glew)

.PHONY: all clean

all: $(BIN)

clean:
	-@rm -vf $(BIN) $(OBJS)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
