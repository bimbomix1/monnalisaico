CFLAGS=-Wall -std=c99

OBJECTS=structure.o
OBJECTS_PRODUCTION= $(OBJECTS) main.o 
OBJECTS_TEST=$(OBJECTS) test_structure.o

mosaico: $(OBJECTS_PRODUCTION)
	gcc $(CFLAGS) $(OBJECTS_PRODUCTION) -o mosaico.o
	mv *.o build/
	build/mosaico.o

test:  $(OBJECTS_TEST)
	gcc $(CFLAGS) $(OBJECTS_TEST) cgreen/cgreen.a -o test.o
	mv *.o build/
	build/test.o

clean:
	rm -rf *.o
