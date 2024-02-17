

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
NAME1 = 3a
NAME2 = 3b
NAME3 = bexeclp
NAME4 = 3c
NAME5 = 1cexeclp
NAME6 = 2cexeclp
#Program wykonawczy
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x
EXEC6 = $(NAME6).x
#Program po kompilacji
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o
OBJS6 = $(NAME6).o
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

$(EXEC4): $(OBJS4) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC5): $(OBJS5) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC6): $(OBJS6) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6)

.PHONY: run1 run2 run3

run1: $(EXEC1)
	./$(EXEC1) $(met) $(num)
run2: $(EXEC2)
	./$(EXEC2) ./$(EXEC3) $(met) $(num)
run3: $(EXEC4)
	./$(EXEC4) ./$(EXEC5) ./$(EXEC6) $(met) $(num)


################################################################
#	Sprzątaczka
################################################################
.PHONY: clean tar
clean:
	rm -f *.o *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvcf $(DIR).tar.gz $(DIR) )