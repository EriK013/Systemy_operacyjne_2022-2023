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
    if (argc < 4){
        printf("Usage: {nazwa pliku execlp} {metoda} {numer sygnału} \n");
        exit(2);
    }
    for (int i = 1; i <= 3; i++){
        switch(pid = fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                execlp(argv[1], argv[1], argv[2], argv[3], NULL);// uruchomienie programu do obsługi procesów z podpunktu a
            default:
                if (signal(atoi(argv[3]), SIG_IGN) == SIG_ERR){// ignorowanie otrzymanego sygnału
                    perror("Funkcja signal ma proglem z ignorowaniem sygnału \n");
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
}