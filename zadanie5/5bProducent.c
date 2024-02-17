#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUF 24

int main(){
    char buffer[BUF];
    int wfd;
    int surowiec;
    surowiec = open("surowiec.txt", O_RDONLY); 
    if (surowiec == -1){
        perror("open surowiec error");
        exit(1);
    }
    // otwarcie potoku do zapisu
    wfd = open("myfifo", O_WRONLY, 0644); 
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
}