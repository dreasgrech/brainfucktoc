OBJECTS = helpers.o printers.o main.o
bftoc: $(OBJECTS)
	gcc -w $(OBJECTS) -o bftoc
printers.o: printers.c header.h
	gcc -c printers.c -Wall
helpers.o: helpers.c header.h
	gcc -c helpers.c -Wall
main.o: main.c header.h
	gcc -c main.c -Wall
clean: 
	rm $(OBJECTS)
