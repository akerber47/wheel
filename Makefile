
BINS=hello sort

all: $(BINS)

CXX=clang++
CXXFLAGS=--std=c++17 -g
# Use C++ to link .o files
LINK.o=$(LINK.cc)


clean:
	rm -f $(BINS) *.o
