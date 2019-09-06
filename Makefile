CXXFLAGS=-std=c++17
CXXFLAGS+=-fsanitize=address
CXXFLAGS+=-O3
CXXFLAGS+=-Wall
CXXFLAGS+=-pedantic

all: foop ffoop

ffoop: foop.cpp
	$(CXX) $(CXXFLAGS) -DBE_MORE_FUNCTIONAL -o ffoop foop.cpp
