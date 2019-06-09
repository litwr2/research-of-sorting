CXXFLAGS = -O3 $(EXTRA)
LDFLAGS = -lstdc++ -lbsd

nsort: nsort.o

nsort.o: nsort.cpp $(wildcard [^z]*.cpp)

clean:
	rm -f *.o nsort always.cpp
