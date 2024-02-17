#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#include "semafory.h"

void clear(){
    usun_semafor("SEM");   
}

int main(int argc, char *argv[]){
    if (argc < 3){
        perror("Usage: ./6 ./wzajemne {liczba procesów potomnych} {liczba sekcji}");
        exit(1);
    }
    int l_sekcji = atoi(argv[3]);
    int n_procesow = atoi(argv[2]);
    sem_t *sem;
    FILE *fp;
    // Inicjalizowanie semafora
    sem = stworz_semafor("SEM", 1);
    // utworzenie pliku numer.txt z wartością 1
    fp = fopen("numer.txt", "w");
    fprintf(fp, "%d", 0);
    fclose(fp);

    // Wywołanie funkcji fork n razy (liczba procesów)
    for(int i = 1; i <= n_procesow; i++){
        switch(fork()) 
            {
                case -1:
                    perror("fork error");
                    exit(1);
                    usun_semafor("SEM");
                case 0:
                    // otwarcie programu do wzajemnego wykluczenia  
                    if (execlp(argv[1], argv[1], "SEM", argv[3], NULL) != 0){
                        perror("execlp error");
                        _exit(3);
                    }
                default:
                    if (signal(SIGINT, clear) == SIG_ERR) {
                        perror("signal error");
                        exit(EXIT_FAILURE);
                    }
                    sleep(1);
            }
       }
       if (signal(SIGINT, clear) == SIG_ERR) {
            perror("signal error");
            exit(EXIT_FAILURE);
       }
        for (int j = 1; j <= n_procesow; j++){
            wait(NULL);
        }
        // SPRAWDZENIE POPRAWNOŚCI OBLICZEŃ
        FILE *fd;
        fd = fopen("numer.txt", "r");
        if (fd == NULL){
            perror("Błąd otwarcia pliku numer");
            exit(1);
        }
        int n;
        fscanf(fd, "%d", &n);
        printf("Końcowa wartość numeru: %d \n", n);
        printf("Poprawna wartość numeru: %d \n", n_procesow * l_sekcji);
        fclose(fd);
        atexit(clear);
    }