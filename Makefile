#Makefile for compiling work
#(C) Benjamin Hugo, 2015
#You are free to modify and reuse this in your own practicals
#This file is in the public domain

CPP=g++
CPPFLAGS=-std=c++11
EXE_NAME=imageops
UNIT_TEST=unitTests
#define a generic rule: to go from .cpp to .o files make should invoke the c++ compiler
#the syntax tells make to invoke the compiler without linking (-c), outputting a .o file reading a .cpp file, additionally specifying flags

$(EXE_NAME): main.o Image.o
	$(CPP) -o $(EXE_NAME) main.o Image.o $(CPPFLAGS) 

Image.o : Image.h Image.cpp
	$(CPP) -c -o Image.o Image.cpp $(CPPFLAGS)

main.o : Image.h main.cpp
	$(CPP) -c -o main.o main.cpp $(CPPFLAGS)
#Never submit binaries to your git repo or vula, so create a rule for cleaning up the binary objects just leaving your source code behind
clean:
	@rm *.o imageops