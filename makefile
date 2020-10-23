CXXFLAGS = -s -O3 -Wno-narrowing $(EXTRA)
LDFLAGS = -lstdc++ -lm -lbsd -pthread

$(FNP): $(FNP).o

$(FNP).o: $(FNP).cpp $(wildcard [^z]*.cpp)

clean:
	rm -f *.o $(FNP) always.cpp
