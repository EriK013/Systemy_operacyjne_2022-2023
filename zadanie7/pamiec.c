#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "pamiec.h"

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

// Tworzenie obiektu pamięci dzielonej
int stworz_pd (const char* name){
    int shm = shm_open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (shm == -1) {
        perror("Błąd tworzenia shm");
        return -1;
    }
    return shm;
}

// Otwieranie obiektu pamięci dzielonej
int otworz_pd (const char *name){
    int shm = shm_open(name, O_RDWR, 0644);
    if (shm == -1) {
        perror("Błąd otwarcia shm");
        return -1;
    }
    return shm;
}

// Ftruncate
int dlugosc_pd (int fd, int length){
    if(ftruncate(fd, length) == -1) {
        perror("Błąd ustalania długości shm");
        return -1;
    }
    return 0;
}

// zamknięcie opd
int zamknij_pd(int fd){
    if(close(fd) == -1){
        perror("Błąd zamknięcia shm");
        return -1;
    }
    return 0;
}

// Usuń pamięć dzieloną
int usun_pd (const char *name){
    if(shm_unlink(name) == -1){
        perror("Błąd usunięcia shm");
        return -1;
    }
    return 0;
}

// Odwzorowanie pamięci dzielonej
void *odwzoruj_pd (size_t length, int fd){
    void *adres = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (adres == MAP_FAILED){
        perror("Błąd odwzorowania");
    }
    return adres;
}

// Usuwanie odwzorowania
int uodwzorowanie_pd (void *adres, size_t length){
    if (munmap(adres, length) == -1) {
        perror("Błąd usuwania odwzorowania");
        return -1;
    }
    return 0;
}


