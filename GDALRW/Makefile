INCLUDE_PATH = -I /usr/local/include
LDFLAGS = -L /usr/local/lib

LIB = -lgdal

CPPFILES = GDALRead.cpp GDALWrite.cpp demo.cpp
OBJECTS  = GDALRead.o GDALWrite.o demo.o
EXECNAME = demo

all:
	g++ -c $(CPPFILES) 
	g++ -o $(EXECNAME) $(OBJECTS) $(LDFLAGS) $(LIB) $(INCLUDE_PATH)

clean:
	rm -rf *.o $(EXECNAME)


 # g++ demo.cpp GDALRead.cpp GDALWrite.cpp -o demo -lgdal