#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUF 24
void clear(){
    if (unlink("myfifo") == -1){
        perror("unlink error");
        exit(1);
    }
}

int main(){
    // otwarcie towaru do zapisu
    int rfd;
    char buffer[BUF];
    int towar;
    towar = open("towar.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (towar == -1){
        perror("open towar");
        exit(1);
    }
    // otwarcie potoku do odczytu
    rfd = open("myfifo", O_RDONLY, 0644);
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