#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include "semafory.h"

// Tworzenie semafora
sem_t *stworz_semafor(const char* name, int value){
    sem_t *sem = sem_open(name, O_CREAT | O_EXCL, 0664, value);
    if (sem == SEM_FAILED) { // obsługa błędów
        perror("Nie udało się stworzyć semafora");
        return NULL;
    }
    return sem;
}

// Otwieranie semafora
sem_t *otworz_semafor(const char* name){
    sem_t *sem = sem_open(name, 0);
    if (sem == SEM_FAILED){ // obsługa błędów
        perror("Nie udało się otworzyć semafora");
        return NULL;
    }
    return sem;
}

// Pobieranie wartości semafora
int wartosc_semafor(sem_t *sem){
    int war;
    sem_getvalue(sem, &war);
    if (war < 0){
        perror("Nie udało się pobrać wartości");
        return -1;
    }
    return war;
}

// Operowanie semaforem
int podnies_semafor(sem_t *sem) {
    if (sem_post(sem) < 0){
        perror("Nie udało się podnieść semafora");
        return -1;
    }
    return 0;
}

int opusc_semafor(sem_t *sem) {
    if (sem_wait(sem) < 0){
        perror("Nie udało się opuścić semafora");
        return -1;
    }
    return 0;
}

// Zamykanie semafora
int zamknij_semafor(sem_t *sem) {
    if (sem_close(sem) < 0){
        perror("Nie udało się zamknąć semafora");
        return -1;
    }
    return 0;
}

// Usuwanie semafora
int usun_semafor(const char *name){
    if (sem_unlink(name) < 0){
        perror("Nie udało się usunąć semafora");
        return -1;
    }
    return 0;
}