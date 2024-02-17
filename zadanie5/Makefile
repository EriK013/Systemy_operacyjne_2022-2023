

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
NAME1 = 5a
NAME2 = 5bProducent
NAME3 = 5bKonsument
#Program wykonawczy
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
#Program po kompilacji
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
#DOLACZANE BIBLIOTEKI
LIBS1 =
#PLIKI NAGLOWKOWE
HEADS1 =
#----------------------------------------------------------------
#OPCJE KOMILATORA I LINKERA
CFLAGS = -Wall
LFLAGS =  -Wall
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
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

.PHONY: run1 run2
run1: $(EXEC1)
	./$(EXEC1) 
	diff -s surowiec.txt towar.txt

run2: 
	mkfifo myfifo -m0644
	xterm -hold -title Producent -e ./$(EXEC2) &
	xterm -hold -title Konsument -e ./$(EXEC3) &
	diff -s surowiec.txt towar.txt
################################################################
#	Sprzątaczka
################################################################
.PHONY: clean tar
clean:
	rm -f *.o *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvcf $(DIR).tar.gz $(DIR) )