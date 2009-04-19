CFLAGS=-Wall -std=c99

OBJECTS=structure.o
OBJECTS_PRODUCTION= $(OBJECTS) main.o 
OBJECTS_TEST=$(OBJECTS) test_structure.o

mosaico: base.o mosaico.o
	gcc $(CFLAGS) base.o mosaico.o -o start.o
	./start.o

base: base.o
	gcc $(CFLAGS) base.c -o base.o


test_structure:  test_structure.o structure.o 
	gcc $(CFLAGS) $(OBJECTS_TEST)  cgreen/cgreen.a -o test_structur.o
	./test_structur.o


test_base:  test_base.o base.o
		gcc $(CFLAGS) base.o test_base.o cgreen/cgreen.a -o test_base_structure.o
		./test_base_structure.o
		
test: test_base test_structure

	
	
clean:
	rm -rf *.o
