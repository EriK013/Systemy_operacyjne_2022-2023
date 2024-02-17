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
#include "pamiec.h"

void clear(){
    usun_semafor("SEMP");
    usun_semafor("SEMK");
    printf("Semafory usunięte! \n");
    usun_pd("/PAMD");
    printf("Pamięć dzielona usunięta! \n");
    exit(0);
}


int main(int argc, char *argv[]){
    if (argc < 3){
        printf("Usage: ./7 ./producent ./konsument \n");
        exit(0);
    }
    //Utworzenie semafora i pamięci dzielonej
    sem_t *semp = stworz_semafor("SEMP", 1);
    sem_t *semk = stworz_semafor("SEMK", 0);
    int pd = stworz_pd("/PAMD");
    dlugosc_pd(pd, 500);


    // Wywołanie dwóch funkcji fork. Jednej dla producenta i drugiej dla konsumenta
    // PRODUCENT
    switch(fork())
    {
        case -1:
            perror("producent fork error");
            exit(1);
        case 0:
            if (execlp(argv[1], argv[1], "SEMP", "SEMK", "/PAMD", NULL) != 0){
                perror("Producent execlp error");
                _exit(2);
            }
        default:
            if (signal(SIGINT, clear) == SIG_ERR){ // W przypadku otrzymania sygnału (CTRL+C) USUN SEMAFOR I PAMIEC DZIELONA
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            sleep(2);
    }
    // KONSUMENT
    switch(fork())
    {
        case -1:
            perror("konsument fork error");
            exit(3);
        case 0:
            if(execlp(argv[2], argv[2], "SEMP", "SEMK", "/PAMD", NULL) != 0){
                perror("konsument execlp error");
                _exit(4);
            }
    }
    if (signal(SIGINT, clear) == SIG_ERR){ // W przypadku otrzymania sygnału (CTRL+C) USUN SEMAFOR I PAMIEC DZIELONA
        perror("signal error");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 2; i++){
        wait(NULL);
    }
    atexit(clear);
}
