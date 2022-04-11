CXX := g++

CXXFLAGS += -std=c++11 -g -Wall -Wextra -pthread
CPPFLAGS += -I. -I include -isystem $(GTEST_DIR)/include

GTEST_DIR = ../googletest/googletest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


SRC := $(wildcard src/*.cpp)

MAIN_SRC := cutSphereMove.cpp
TEST_SRC := test/testComponents.cpp

all: cutSphereMove

test.asc: cutSphereMove
	./cutSphereMove

testComponents: $(TEST_SRC) $(SRC) gtest_main.a
	g++ -I$(GTEST_HEADERS) $(CXXFLAGS) $(CPPFLAGS) -lpthread $^ -o $@

cutSphereMove: $(MAIN_SRC) $(SRC)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^

clean:
	rm -f cutSphereMove testComponents gmock.a gmock_main.a *.o

showImage: cutSphereMove test.asc
	./PointVisualizer_linux64 test.asc


# build googletest

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
