CXXFLAGS = -O3 
LDFLAGS = -lstdc++ -lbsd

nsort: nsort.o

nsort.o: nsort.cpp

clean:
	rm *.o nsort
