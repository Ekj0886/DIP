CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXE = EXE_NAME
CPP = MAIN_NAME
HEAD = HEAD_NAME

all: clean main

main: $(CPP).o $(HEAD).o
	$(CXX) $(CXXFLAGS) $(CPP).o $(HEAD).o -o $(EXE)

$(CPP).o: $(CPP).cpp $(HEAD).h
	$(CXX) $(CXXFLAGS) -c $(CPP).cpp

$(HEAD).o: $(HEAD).cpp $(HEAD).h
	$(CXX) $(CXXFLAGS) -c $(HEAD).cpp

clean:
	rm -rf *.o $(EXE)