
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
                sleep(5);
                printf("Proces potomny  ");
                printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));
            default:
            	sleep(1);
        }
    }
    
}
/* Proces macierzysty ma mniejszą wartość n funkcji sleep(n), więc zostanie on zakończony wcześniej niż 
proces potomny. W tym przypadku przy wywołaniu funkcji getppid() dla procesu potomnego jego wartość będzie wskazywała na indeks procesu, który zaadoptował osierocony proces. W celu zlokalizowania tego procesu za pomocą pstree -a wystarczy zlokalizować proces o pid==ppid procesów osieroconych. Ze względu na charakterystykę funkcji fork w pętli for maksymalna ilość procesów osieroconych w jednym momencie może wynosić 4 */
