#----------------------------------------------------------------
#ROZSZERZENIA NAZW PLIKÓW
# Dodanie .c
.SUFFIXES: .c .o .x .h
#----------------------------------------------------------------
#OBSLUGA NAZWY KATALOGU
DIR = $(notdir $(CURDIR))
#Nazwa systemu operacyjnego
SYSNAME = $(shell uname -s)
#RDZENIE NAZW PLIKÓW
NAME1 = zad7
NAME2 = producent
NAME3 = konsument
NAME4 = pamiec
#----------------------------------------------------------------
#OPCJE KOMILATORA I LINKERA
Cflags = -o
Lflags = -c
#Biblioteki linkera
LDLIBS = -lm
#Kopilator i linker
CO = gcc
LD = $(CO)
#Archiwizer do tworzenia bibliotek statycznych
AR = ar
#Opcje archiwizera
ARFLAGS = rsv

################################################################
#	REGULY ZALEZNOSCI
################################################################
pamiec.o: pamiec.h pamiec.c
	$(CO) $(Lflags) pamiec.c 

producent.o: producent.c
	$(CO) $(Lflags) producent.c 

konsument.o: konsument.c
	$(CO) $(Lflags) konsument.c 

zad7.o: zad7.c 
	$(CO) $(Lflags) zad7.c

## Biblioteka statyczna
libStat.a : pamiec.o
	ar rsv libStat.a pamiec.o
	mkdir -p ./lib
	mv libStat.a ./lib
	rm -f ./Stat

zad7s.x: 
	$(CO) $(Cflags) zad7s.x -O zad7.o -L./lib -lStat -lm -lpthread -lrt

producents.x: producent.c
	$(CO) $(Cflags) producents.x -O producent.o -L./lib -lStat -lm -lpthread -lrt 

konsuments.x: konsument.c
	$(CO) $(Cflags) konsuments.x -O konsument.o -L./lib -lStat -lm -lpthread -lrt

## Biblioteka dynamiczna (dzielona)
libShar.so: pamiec.o 
	$(CO) -shared $(Cflags) libShar.so pamiec.o
	mkdir -p ./lib
	mv libShar.so ./lib

zad7d1.x: 
	gcc -o zad7d1.x -O zad7.o -L./lib -lShar -lm -lpthread -lrt -Wl,-R ./lib 

producentd1.x: 
	gcc -o producentd1.x -O producent.o -L./lib -lShar -lm -lpthread -lrt -Wl,-R ./lib

konsumentd1.x: 
	gcc -o konsumentd1.x -O konsument.o -L./lib -lShar -lm -lpthread -lrt -Wl,-R ./lib


.PHONY: all
all:  zad7.o konsument.o producent.o libStat.a zad7s.x konsuments.x producents.x libShar.so konsumentd1.x producentd1.x zad7d1.x

.PHONY: run1static run1dynamic

run1static: zad7s.x
	./zad7s.x ./producents.x ./konsuments.x
	diff -s towar.txt surowiec.txt

run1dynamic: zad7d1.x
	./zad7d1.x ./producentd1.x ./konsumentd1.x
	diff -s towar.txt surowiec.txt

################################################################
#	Sprzątaczka
################################################################
.PHONY: clean tar
clean:
	rm -f *.o *~ *.a *.so *.x core core* a.out; rm -rf ./lib
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )