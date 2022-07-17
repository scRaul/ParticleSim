
sim: main.o ppm.o
	g++-11 -o sim main.o ppm.o
main.o: main.cpp PPM.hpp particle.hpp
	g++-11 -c main.cpp
ppm.o: ppm.cpp PPM.hpp
	g++-11 -c ppm.cpp
	
clean:
	rm -f *~ *.o sim

fresh:
	rm -f img/*.png img/*.ppm
