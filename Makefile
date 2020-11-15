
BINS=hello.out

all: $(BINS)

hello.out: hello/main.o
	$(CXX) $(CXXFLAGS) -o hello.out hello/main.o

CXX=clang++
CXXFLAGS=--std=c++17 -g
# Use C++ to link .o files
LINK.o=$(LINK.cc)


clean:
	rm -f $(BINS) hello/*.o
