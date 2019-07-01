CXXFLAGS = -g $(EXTRA)
LDFLAGS = -lstdc++ -lbsd
FN = nsort2

$(FN): $(FN).o

$(FN).o: $(FN).cpp $(wildcard [^z]*.cpp)

clean:
	rm -f *.o $(FN) always.cpp
