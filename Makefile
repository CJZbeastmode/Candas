CC=gcc
CFLAGS=-I.
OBJECTS=playground.o dynarrint.o dynarrstr.o dynarrchar.o sortNumber.o sortAlphabet.o helper.o candas.o

candas:
	cd src; make; make move; cd ..;\
	$(CC) -std=c11 -c playground.c;\
	$(CC) -std=c11 -o candas $(OBJECTS);\
	make clean

clean:
	rm *.o

remove:
	rm candas