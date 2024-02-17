#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    printf("Proces macierzysty UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d \n", getuid(), getgid(), getpid(), getppid(), getpgid(0));
    for(int i = 1; i <= 3; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                setpgid(0, 0);
                printf("Proces potomny  ");
                printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));
            default:
                wait(NULL);
        }
    }
    
}

/* Kazde wywolanie funkcji fork tworzy jeden proces potomny.
Wywolanie funkcji fork() w petli for tworzy 2^N procesow (liczac z procesem macierzystym) a
2^N - 1 procesow potomnych. Gdzie N jest liczba iteracji petli dzieje sie tak dlatego, ze przy wywolaniu
fork() tworzy sie nowy proces potomny jednak dziedziczy on wartosc i (iteracji petli) swojego procesu macierzystego
Przykladowo niech nasz proces macierzysty(P1) ma i==1. Wywolana jest funkcja fork() i tworzy sie nowy proces(P2) o i==1
Nastepnie zwieksza sie wartosc i w obu procesach o 1. Maciecierzysty ma wiec i==2 i potomny ma i == 2
Warunek konczacy petle w tych obu procesach (i <= 2) nie jest spelniony i w obu tych procesach wywolywana jest funkcja fork().
Z P(2)(i==2) powstaje P(3) jest to iteracja, wiec i(P2) == i(P3) wynosza 3, wiec nie powstana juz nowe procesy.
Z P(1)(i==2) powstaje P(4) i sytuacja jak wyzej.
Mamy wiec jeden oryginalny proces macierzysty P(1) oraz trzy procesy potomne P(2)P(3)P(4) co jest równe naszemu wzorowi 2^N.*/