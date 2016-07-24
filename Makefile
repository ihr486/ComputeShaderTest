CXXSRCS := $(wildcard *.cpp)
CXXOBJS := $(CXXSRCS:%.cpp=%.o)
OBJS := $(CXXOBJS)

BIN := cstest

CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -O2 $(shell pkg-config --cflags glfw3 glew)
LDFLAGS := $(shell pkg-config --libs glfw3 glew)

.PHONY: all clean

all: $(BIN)

clean:
	-@rm -vf $(BIN) $(OBJS)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
