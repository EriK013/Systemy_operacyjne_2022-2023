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
#include <stdbool.h>

#define N 3
int wspolny_num = 0;
int wybieranie[N];
int numer[N];


void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH\033[2K", y, x);
}



void* Proces_i(void *arg){
    int wlasny_num;
    int nr_procesu = *(int *)arg;
    srand(time(NULL));
    int max;
    while(1){
        // Sekcja prywatna
        sleep(rand() % 2);
        gotoxy(1, nr_procesu);
        printf("\033[0mWątek %d wykonuje sekcje prywatną\033[0m\n", nr_procesu);
        sleep(rand() % 2);
        gotoxy(1, nr_procesu);
        printf("\033[33mWątek %d czeka na wejście do sekcji krytycznej \033[0m\n", nr_procesu);
        
        wybieranie[nr_procesu - 1] = 1;
        max = 0;
        for (int j = 0; j < N; j++){ // numer[i] = max(numer[0], ..., numer[n-1]) + 1;
            if (numer[j] > max){
                max = numer[j];
            }
        }
        numer[nr_procesu - 1] = max + 1;
        wybieranie[nr_procesu - 1] = 0;
        for (int i = 0; i < N; i++){
            while (wybieranie[i]){ // Sprawdzanie czy inny wątek nie wybiera liczby

            }
            while(numer[i] != 0 && (numer[i] < numer[nr_procesu - 1] || (numer[i] == numer[nr_procesu - 1] && i < (nr_procesu - 1)))) { // Ustalenie kolejności

            }
        }
        
        // CZĘŚĆ KRYTYCZNA
        gotoxy(70, nr_procesu);
        printf("\033[41m Wątek %d wykonuje sekcje krytyczną \033[0m\n", nr_procesu);
        wlasny_num = wspolny_num;
        wlasny_num++;
        sleep((rand() % 6) + 1);
        wspolny_num = wlasny_num;
        gotoxy(1, nr_procesu);
        printf("\033[30m Wątek %d wychodzi z sekcji krytycznej \033[0m\n", nr_procesu);
        numer[nr_procesu - 1] = 0;

        // RESZTA
        sleep(rand() % 2);
        break;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t ID[N];
    int p_id[N];
    for (int j = 0; j < N; j++){
        wybieranie[j] = 0;
        numer[j] = 0;
    }
    for (int i = 0; i < N; i++){
        ID[i] = i;
        p_id[i] = i + 1;
        if (pthread_create(&ID[i], NULL, &Proces_i, (void *)&p_id[i]) != 0 ){
            perror("Blad tworzenia wątku");
            exit(EXIT_FAILURE);   
        }
    }

    // Czekanie na zakończenie wątków
    for (int i = 0; i < N; i++){
        if (pthread_join(ID[i], NULL) != 0){
            perror("Blad zakończenia wątku");
            exit(EXIT_FAILURE);
        }                
    }
    printf("\e[1;1H\e[2J");

    printf("Numer końcowy: %d \n", wspolny_num);

}