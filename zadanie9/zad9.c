#ifndef _REENTRANT
#define _REENTRANT
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

pthread_mutex_t processMutex;
int wspolny_num = 0;
int liczba_sekcji;
int liczba_watkow;

void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH\033[2K", y, x);
}

// sekcja krytyczna
static void* wykluczenie(void *arg)
{
    srand(time(NULL));
    int lokalny_num;
    int *ID = arg;
    for(int i = 0; i < liczba_sekcji; i++)
    {
        // WŁASNE SPRAWY
        gotoxy(1, *ID);
        printf("\033[0mWątek %d wykonuje własne sprawy \033[0m\n", *ID);;
        //sleep(rand() % 3);

        // CZĘŚĆ KRYTYCZNA
        pthread_mutex_lock(&processMutex); // zamknięcie mutexu
        lokalny_num = wspolny_num;
        lokalny_num++;
        gotoxy(70, *ID);
        printf("\033[41m Wątek %d wykonuje sekcje krytyczną \033[0m \n", *ID);
        sleep((rand() % 5) + 1);
        wspolny_num = lokalny_num;
        pthread_mutex_unlock(&processMutex); // otwarcie mutexu  

        // RESZTA  
        gotoxy(1, *ID);
        printf("\033[2mWątek %d wykonuje resztę \033[0m", *ID);
        sleep(1);   
    }
}

int main(int argc, char *argv[]){
    // sprawdzanie argumentów
    if (argc < 2){
        printf("Usage: ./9 liczba_sekcji liczba_wątków\n");
        exit(1);
    }
    liczba_sekcji = atoi(argv[1]);
    liczba_watkow = atoi(argv[2]);

    pthread_t ID[liczba_watkow]; // ustalenie ID wątków
    for (int i = 0; i < liczba_sekcji; i++){
        ID[i] = i + 1;
    }

    // inicjalizowanie mutexu
    if (pthread_mutex_init(&processMutex, NULL) != 0){
        perror("Blad inicjalizacji mutexu");
        exit(EXIT_FAILURE);
    }

    // Tworzenie wątków i realizowanie wzajemnego wykluczenie
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < liczba_watkow; i++){
        int *t_id = malloc(sizeof(int));
        *t_id = i + 1;
        if (pthread_create(&ID[i], NULL, &wykluczenie, (void*)t_id) != 0){
            perror("Blad tworzenia wątku");
            exit(EXIT_FAILURE);    
        }
    }

    // Czekanie na zakończenie wątków
    for (int i = 0; i < liczba_watkow; i++){
        if (pthread_join(ID[i], NULL) != 0){
            perror("Blad zakończenia wątku");
            exit(EXIT_FAILURE);
        }                
    }

    printf("\e[1;1H\e[2J");

    // zamykanie mutexu
    if (pthread_mutex_destroy(&processMutex) != 0){
        perror("Blad zamykania mutexu");
        exit(EXIT_FAILURE);
    }
    printf("Wartość końcowa wspólnego num: %d\n", wspolny_num);
    printf("Wartość końcowa powinna wynosić %d\n", liczba_sekcji * liczba_watkow);
}
