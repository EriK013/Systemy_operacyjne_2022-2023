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
    int wB = 0; // liczba zapisanych bajtów
    int towar = open("towar.txt",  O_WRONLY | O_CREAT | O_TRUNC, 0644); //  otwarcie surowca
    if (towar == -1){
        perror("Błąd otwarcia surowca");
        _exit(EXIT_FAILURE);
    }
    sem_t *semp = otworz_semafor(sem_pname); // Otwarcie semaforu
    sem_t *semk = otworz_semafor(sem_kname);
    int pd_adress = otworz_pd(pd_name); // otwarcie pamięci dzielonej
    SegmentPD *wpd = (SegmentPD *) odwzoruj_pd(sizeof(SegmentPD), pd_adress); // odwzorowanie pamięci dzielonej
    wpd->wyjmij = 0;
    srand(time(NULL));
    do
    {
        opusc_semafor(semk);
        printf("***SEMAFOR KONSUMENTA OPUSZCZONY : %i \n \n", wartosc_semafor(semk));
        wB = write(towar, wpd->buffer[wpd->wyjmij], wpd->rB);
        printf("Konsument odczytał %i bajtów: %s \n \n", wB, wpd->buffer[wpd->wyjmij]);
        wpd->wyjmij = (wpd->wyjmij + 1) % NBUF;
        sleep(rand()%2);
        podnies_semafor(semp);
        printf("***SEMAFOR PRODUCENTA PODNIESIONY : %i \n \n", wartosc_semafor(semp));
        if (wpd->rB == 0){
            break;
        }
    } while (1);
    
    close(towar);
    zamknij_semafor(semp);
    zamknij_semafor(semk);
    zamknij_pd(pd_adress);
}

