SRC := $(wildcard src/*.cpp)
CFLAGS = -I. -Wall -std=c++11 -I include

all: cutSphereMove

test.asc: cutSphereMove
	./cutSphereMove

cutSphereMove: cutSphereMove.cpp $(SRC)
	g++ -o $@ $^ $(CFLAGS)

test: test_iterations.cpp $(SRC)
	g++ -o $@ $^ $(CFLAGS)

clean:
	rm cutSphereMove test

show_image: cutSphereMove test.asc
	./cutSphereMove
	./PointVisualizer_linux64 test.asc
