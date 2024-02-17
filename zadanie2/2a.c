#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    printf("Proces macierzysty UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d \n", getuid(), getgid(), getpid(), getppid(), getpgid(0)); //  Wyswietlenie identyfikatorow dla pierwszego procesu macierzystego (Lidera grupy wszystkich procesow potomnych)
    for(int i = 1; i <= 3; i++) 
    {
        switch(fork()) // Funkcja fork() jest wywoływana
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                execlp(argv[1], argv[1], NULL); // Wywołanie execl i przekazanie nazwy pliku za pomoca parametru z terminala
            default:
                wait(NULL);
        }
    }
    
} 