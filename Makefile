SRC := $(wildcard src/*.cpp)
SRC += cutSphereMove.cpp
CFLAGS = -I. -Wall -std=c++11 -I include

all: cutSphereMove

cutSphereMove: $(SRC)
	g++ -o $@ $^ $(CFLAGS)

test: test_iterations.cpp
	g++ -o $@ $^ $(CFLAGS)

clean:
	rm cutSphereMove test
