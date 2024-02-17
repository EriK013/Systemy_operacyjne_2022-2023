#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include "semafory.h"

void sekcja_krytyczna(){
    int num;
    FILE* fp;
    // Otwarcie pliku numer
    fp = fopen("numer.txt", "r");
    if (fp == NULL){
        perror("Błąd otwarcia pliku numer");
        exit(1);
    }
    fscanf(fp, "%d", &num); // pobranie wartości z numeru
    fclose(fp);
    num++; // zwiekszenie wartości o 1
    printf ("Proces o PID: %d wykonuje sekcje krytyczna \n", getpid());
    srand(time(NULL));
    sleep(rand() % 5); // Czekanie procesu
    // zapisanie wartości z powrotem do pliku
    printf("Proces o PID: %d nadpisuje wartość \n", getpid());
    fp = fopen("numer.txt", "w");
    if (fp == NULL){
        perror("Błąd otawrcia plik");
        exit(1);
    }
    fprintf(fp, "%d", num);
    fclose(fp);
}

int main(int argc, char **argv){
    // Otwarcie semafora
    int liczba_sekcji = atoi(argv[2]);
    char *nazwa_semaforu = argv[1];
    sem_t *sem = otworz_semafor(nazwa_semaforu);

    for (int i = 0; i < liczba_sekcji; i++) {
        //***WŁASNA SPRAWA***
        printf("Proces o PID: %d wykonuje własne sprawy \n", getpid());
        srand(time(NULL));
        sleep(rand() % 3);

        //***CZĘŚĆ KRYTYCZNA***
        if(opusc_semafor(sem) != 0){
            perror("błąd semafora");
            _exit(1);
        }
        printf("***SEMAFOR OPUSZCZONY. WARTOŚĆ : %d \n", wartosc_semafor(sem));
        printf("Proces o PID: %d wchodzi do sekcji krytycznej \n", getpid());
        sekcja_krytyczna();
        printf("Proces o PID: %d opuszcza sekcje krytyczną \n", getpid());
        if(podnies_semafor(sem) != 0){
            perror("bład semafora");
            _exit(2);
        }
        printf("***SEMAFOR PODNIESIONY. WARTOŚĆ : %d \n", wartosc_semafor(sem));

        //***RESZTA***
        printf("Proces o PID: %d wykonuje reszte \n", getpid());
        srand(time(NULL));
        sleep(rand() % 3);
        printf("Zakończenie działania procesu %d \n", getpid());
    }
}