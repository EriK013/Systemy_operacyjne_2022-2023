/* Wywołać funkcję fork trzy razy (najlepiej w pętli for) i wypisać powyższe identyfikatory dla procesu macierzystego 
oraz wszystkich procesów potomnych. Przy pomocy funkcji wait sprawić, aby proces macierzysty zaczekał na zakończenie
wszystkich procesów potomnych.*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
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
                printf("Proces potomny  "); //  Wyswietlenie identyfikatorow dla kazdego z procesow potomnych
                printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));
            default:
                if(wait(NULL) != -1){ //Wyświetla wiadomość o zakończeniu trwania wait() (zakonczenie jednego procesu potomnego) można zastąpić default: wait(NULL); dla większej przejrzystości 
                printf("Proces skończył czekać PID %d PPID %d\n", getpid(), getppid());
                }
        }
    }
    
}