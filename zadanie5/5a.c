#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUF 24

void clear(){
    if (unlink("fifo") == -1){
        perror("unlink error");
        exit(1);
    }
}

int main()
{
    int wfd, rfd; // wfd: write file descriptor rfd: read file descriptor
    char buffer[BUF];
    // Utworzenie potoku nazwanego
    if (mkfifo("fifo", 0644) == -1){
        perror("Tworzenie kolejki FIFO");
        exit(1);
    }

    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(1);
        case 0: ;// producent
            // otwarcie surowca do oczytu
            int surowiec;
            surowiec = open("surowiec.txt", O_RDONLY); 
            if (surowiec == -1){
                perror("open surowiec error");
                exit(1);
            }
            // otwarcie potoku do zapisu
            wfd = open("fifo", O_WRONLY, 0644); 
            if (wfd == -1){
                perror("open error");
                exit(1);
            }
            // Odczyt z surowca i zapis do potoku
            int lp;
            while ((lp = read(surowiec, buffer, BUF)) > 0){
                if (write(wfd, buffer, lp) == -1){
                    perror("write");
                    exit(1);
                }
                printf("Producent: %s \n", buffer);
                sleep(rand() % 3);
            }
            close(surowiec);
            close(wfd);
            exit(0);
         default: ;// konsument
            // otwarcie towaru do zapisu
            int towar;
            towar = open("towar.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
            if (towar == -1){
                perror("open towar");
                exit(1);
            }
            // otwarcie potoku do odczytu
            rfd = open("fifo", O_RDONLY, 0644);
            // Odczyt z potoku i zapis do surowca
            int lk;
            while ((lk = read(rfd, buffer, BUF)) > 0){
                if (write(towar, buffer, lk) == -1){
                    perror("write to towar");
                    exit(1);
                }
                printf("Konsument %s \n", buffer);
                sleep(rand() % 3);
            }
            close(towar);
            close(rfd);
            if (atexit(clear) != 0){ // usuwanie potoku
                perror("Atexit error");
            }
            exit(0);
    }
}