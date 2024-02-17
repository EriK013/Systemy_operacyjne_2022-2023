#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]){
    int pid;
    int status;
    int *stat_loc = &status;
    if (argc < 3){
        printf("Usage: make run2 met={metoda} num={numer sygnału} \n");
        exit(2);
    }
    switch(pid = fork())
    {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            execlp(argv[1], argv[1], argv[2], argv[3], NULL); // uruchomienie programu z 3a w procesie potomnym
        default:
            sleep(2); // proces macierzysty czeka na zainicjalizowanie procesu potomnego
            if (kill(pid, 0) == 0){ // sprawdzenie czy proces potomny istnieje
                 kill(pid, atoi(argv[3])); // wysłanie sygnału do procesu potomnego
            }
            wait(stat_loc);
            printf("Proces potomny o PID: %d zakończył działanie \n", pid); // Czekanie na zakończenie działania procesu potomnego i zwrócenie jego PID
            if (WIFSIGNALED(status)){
                char *str = strsignal(WTERMSIG(status));
                printf("Proces został zakończony przez sygnał %d %s\n", WTERMSIG(status), str);
            }         
    }
}

