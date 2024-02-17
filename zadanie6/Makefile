

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
NAME1 = powielacz_procesow
NAME2 = wzajemne_wykluczenie
NAME3 = semafory
#----------------------------------------------------------------
#OPCJE KOMILATORA I LINKERA
Cflags = 
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
semafory.o: semafory.h semafory.c
	$(CO) $(Lflags) semafory.c -lpthread

wzajemne_wykluczenie.x: wzajemne_wykluczenie.c semafory.o
	$(CO) $(Cflags) -o $@ $^ -lpthread

powielacz_procesow.x : powielacz_procesow.c semafory.o wzajemne_wykluczenie.o
	$(CO) $(Cflags) -o $@ powielacz_procesow.c semafory.o -lpthread

.PHONY: all
all: powielacz_procesow.x wzajemne_wykluczenie.x semafory.o

.PHONY: run1
run1: powielacz_procesow.x
	./powielacz_procesow.x ./wzajemne_wykluczenie.x $(l_p) $(l_s) 
	rm numer.txt

################################################################
#	Sprzątaczka
################################################################
.PHONY: clean tar
clean:
	rm -f *.o *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvcf $(DIR).tar.gz $(DIR) )