CXXFLAGS = -O3 
LDFLAGS = -lstdc++ -lbsd

nsort: nsort.pas timer.o
	fpc -O3 $<

timer.o: timer.c

clean:
	rm -f *.o nsort *.o
