#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include "pamiec.h"

#define NELE 20 // Rozmiar elementu bufora w bajtach
#define NBUF 5 // Liczba elementow bufora

typedef struct {
    char buffer[NBUF][NELE];
    int wstaw, wyjmij, rB;
} SegmentPD;

int main(int argc, char *argv[]){
    char *sem_pname = argv[1];
    char *sem_kname = argv[2];
    char *pd_name = argv[3];
    int rB; // liczba przeczytanych bajtów
    int surowiec = open("surowiec.txt", O_RDONLY, 0644); //  otwarcie surowca
    if (surowiec == -1){
        perror("Błąd otwarcia surowca");
        _exit(EXIT_FAILURE);
    }
    sem_t *semp = otworz_semafor(sem_pname); // Otwarcie semaforu producenta i konsumenta
    sem_t *semk = otworz_semafor(sem_kname);
    int pd_adress = otworz_pd(pd_name); // otwarcie pamięci dzielonej
    SegmentPD *wpd = (SegmentPD *) odwzoruj_pd(sizeof(SegmentPD), pd_adress); // odwzorowanie pamięci dzielonej
    wpd->wstaw = 0;
    wpd->rB = 1;
    srand(time(NULL));

    do
    {
        opusc_semafor(semp); // opuść semafor
        printf("***SEMAFOR PRODUCENTA OPUSZCZONY : %i \n \n", wartosc_semafor(semp));
        rB = read(surowiec, wpd->buffer[wpd->wstaw], NELE); // czytamy z surowca i zapisujemy w naszym buforze   
        if(rB == -1){
            perror("read error\n");
            _exit(EXIT_FAILURE);
        }
        printf("Producent przesłał %i bajtów: %s\n \n", rB, wpd->buffer[wpd->wstaw]);
        wpd->wstaw = (wpd->wstaw + 1) % NBUF; // Przesuwamy inteks
        wpd->rB = rB;
        sleep(rand()%2);
        podnies_semafor(semk);
        printf("***SEMAFOR KONSUMENTA PODNIESIONY : %i\n \n", wartosc_semafor(semk));
    }while(rB > 0);
    
    close(surowiec);
    zamknij_semafor(semp);
    zamknij_semafor(semk);
    zamknij_pd(pd_adress);
}
