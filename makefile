CXXFLAGS = -O3 $(EXTRA)
LDFLAGS = -lstdc++ -lbsd

$(FNP): $(FNP).o

$(FNP).o: $(FNP).cpp $(wildcard [^z]*.cpp)

clean:
	rm -f *.o $(FNP) always.cpp
