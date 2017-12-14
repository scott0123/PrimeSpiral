EXENAME = primeSpiral
OBJS = main.o png.o rgbapixel.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp ../PNG/png.h ../PNG/rgbapixel.h
	$(CXX) $(CXXFLAGS) main.cpp

png.o : ../PNG/png.cpp ../PNG/png.h ../PNG/rgbapixel.h
	$(CXX) $(CXXFLAGS) ../PNG/png.cpp

rgbapixel.o : ../PNG/rgbapixel.cpp ../PNG/rgbapixel.h
	$(CXX) $(CXXFLAGS) ../PNG/rgbapixel.cpp

clean :
	-rm -f *.o $(EXENAME)
