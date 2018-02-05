.PHONY:all

TARGETS=mrt unit-test

all: $(TARGETS)

clean:
	@rm -f *.o ./lodepng-master/lodepng.o *~ $(TARGETS) *.d

CC=g++
CFLAGS=-Wall -std=c++11 -g -I./glm-0.9.8.4/glm/ -fopenmp -I./lodepng-master/ -O3
sources=main.cpp image.cpp raytracer.cpp scene.cpp kdtree.cpp ./lodepng-master/lodepng.cpp unit-test.cpp

OBJ=main.o

# compile
%.o: %.cpp
	$(CC) -c $(CFLAGS) $*.cpp -o $*.o

%.d: %.cpp        
	@echo “make $@“
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

mrt: main.o image.o scene.o raytracer.o kdtree.o ./lodepng-master/lodepng.o
	$(CC) $(CFLAGS) $^ -o $@

unit-test: unit-test.o image.o raytracer.o scene.o raytracer.o kdtree.o ./lodepng-master/lodepng.o
	$(CC) $(CFLAGS) $^ -o $@

include $(sources:.cpp=.d)
