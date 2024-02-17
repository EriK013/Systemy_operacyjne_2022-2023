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
                printf("Proces potomny  ");
                printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));
                sleep(2);
            default:
                sleep(1.5);
        }
    }
    
}

/* Przykładowy output:
Proces macierzysty UID: 1000, GID: 1000, PID: 12299, PPID: 818, PGID: 12299 //najstarsze pokolenie
Proces potomny  UID: 1000, GID: 1000, PID: 12300, PPID: 12299, PGID: 12299  }
Proces potomny  UID: 1000, GID: 1000, PID: 12312, PPID: 12299, PGID: 12299   } //dzieci najstarszego pokolenia
Proces potomny  UID: 1000, GID: 1000, PID: 12323, PPID: 12299, PGID: 12299  } 
Proces potomny  UID: 1000, GID: 1000, PID: 12339, PPID: 12300, PGID: 12299  }
Proces potomny  UID: 1000, GID: 1000, PID: 12386, PPID: 12300, PGID: 12299   } // kolejne pokolenie "rodzeństwo"
Proces potomny  UID: 1000, GID: 1000, PID: 12385, PPID: 12312, PGID: 12299  }
Proces potomny  UID: 1000, GID: 1000, PID: 12396, PPID: 12339, PGID: 12299  // najmłodsze pokolenie
*/