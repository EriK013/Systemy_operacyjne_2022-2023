#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]){
    int pgid, pid;
    int status;
    int *stat_loc = &status;
    if (argc < 5){
        printf("Usage:make run3 met={metoda} num={numer sygnału} \n");
        exit(2);
    }
    switch(pid = fork())
    {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            setpgid(0, 0); // nadanie statusu lidera procesowi potomnemu
            execlp(argv[1], argv[1], argv[2], argv[3], argv[4], NULL); // uruchomienie procesu potomnego
        default:
            sleep(2); // proces macierzysty czeka na zainicjalizowanie procesu potomnego
            pgid = getpgid(pid); // pobranie pgid procesu potomnego do zmiennej pgid
            for (int i = 1; i <= 3; i++){ // wysyłanie będą 3 sygnały ponieważ tyle programów potomnych do obsługi sygnałów jest tworzonych przez execlp
                if (kill(-pgid, 0) == 0){ // wysłanie sygnału do procesu potomnego będącego liderem grupy po uprzednim sprawdzeniu czy taka grupa istnieje
                    kill(-pgid, atoi(argv[4]));
                    sleep(2);
                }
            }
            wait(stat_loc); // proces macierzysty czeka na zakończenie swojego potomka 
            printf("Proces potomny o PID: %d zakończył działanie \n", pid);    
            // informacje o zakończeniu procesu
            if (WIFSIGNALED(status)){
                char *str = strsignal(WTERMSIG(status));
                printf("Proces został zakończony przez sygnał %d %s\n", WTERMSIG(status), str);
            }         
    }
}