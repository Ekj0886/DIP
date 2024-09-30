CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXE = HW1
CPP = main
HEAD = IMAGE

all: clean main

main: $(CPP).o $(HEAD).o BMP.o
	$(CXX) $(CXXFLAGS) $(CPP).o $(HEAD).o BMP.o -o $(EXE)

$(CPP).o: $(CPP).cpp $(HEAD).h
	$(CXX) $(CXXFLAGS) -c $(CPP).cpp

$(HEAD).o: $(HEAD).cpp $(HEAD).h 
	$(CXX) $(CXXFLAGS) -c $(HEAD).cpp

BMP.o: BMP.cpp BMP.h
	$(CXX) $(CXXFLAGS) -c BMP.cpp

clean:
	rm -rf *.o $(EXE)