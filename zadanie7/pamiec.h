#ifndef PAMIEC_H
#define PAMIEC_H

sem_t *stworz_semafor(const char* name, int value);
sem_t *otworz_semafor(const char* name);
int wartosc_semafor(sem_t *sem);
int podnies_semafor(sem_t *sem);
int opusc_semafor(sem_t *sem);
int zamknij_semafor(sem_t *sem);
int usun_semafor(const char *name);
int stworz_pd (const char* name);
int otworz_pd (const char *name);
int dlugosc_pd (int fd, int length);
int zamknij_pd(int fd);
int usun_pd (const char *name);
void *odwzoruj_pd (size_t length, int fd);
int uodwzorowanie_pd (void *adres, size_t length);

#endif