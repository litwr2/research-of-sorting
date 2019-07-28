CXXFLAGS = -O3 $(EXTRA)
LDFLAGS = -lstdc++ -lbsd -Wno-narrowing

$(FNP): $(FNP).o

$(FNP).o: $(FNP).cpp $(wildcard [^z]*.cpp)

clean:
	rm -f *.o $(FNP) always.cpp
