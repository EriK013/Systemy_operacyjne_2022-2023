#ifndef SEMAFORY_H
#define SEMAFORY_H

sem_t *stworz_semafor(const char* name, int value);
sem_t *otworz_semafor(const char* name);
int wartosc_semafor(sem_t *sem);
int podnies_semafor(sem_t *sem);
int opusc_semafor(sem_t *sem);
int zamknij_semafor(sem_t *sem);
int usun_semafor(const char *name);

#endif