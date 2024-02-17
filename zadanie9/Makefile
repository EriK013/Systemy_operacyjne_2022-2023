#----------------------------------------------------------------
#ROZSZERZENIA NAZW PLIKÓW
# Dodanie .c
.SUFFIXES: .c
#----------------------------------------------------------------
#OBSLUGA NAZWY KATALOGU
DIR = $(notdir $(CURDIR))
#Nazwa systemu operacyjnego
SYSNAME = $(shell uname -s)
#RDZENIE NAZW PLIKÓW
NAME1 = zad9
#Program wykonawczy
EXEC1 = $(NAME1).x
#Program po kompilacji
OBJS1 = $(NAME1).o
#DOLACZANE BIBLIOTEKI
LIBS1 =
#PLIKI NAGLOWKOWE
HEADS1 =
#----------------------------------------------------------------
#OPCJE KOMILATORA I LINKERA
CFLAGS =
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
%.o: %.c
	$(CO) $(CFLAGS) -c $<

#Jawna reguła zależności
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $^ -lpthread -lrt

.PHONY: all
all: $(EXEC1)

.PHONY: run1
run1: $(EXEC1)
	./$(EXEC1) $(l_s) $(l_w)

################################################################
#	Sprzątaczka
################################################################
.PHONY: clean tar
clean:
	rm -f *.o *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvcf $(DIR).tar.gz $(DIR) )