#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX 24

int main(){
    int filedes[2];
    char bufor[MAX];
    if (pipe(filedes) == -1){ // tworzenie potoku
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    switch (fork())
    {
        case -1:
            perror("fork error");
            exit(1);
        case 0: ;// producent
            int surowiec;
            int l_p; // liczba bajtów przeczytanych przez producenta
            close(filedes[0]); // zamknięcie niużywanego końca potoku (do odczytu)
            if ((surowiec = open("surowiec.txt", O_RDONLY)) == -1){ // utworzenie deskryptora pliku "surowiec.txt" z flagą otwórz plik do czytania
                perror("otwarcie surowca \n");
                exit(EXIT_FAILURE);
            }
            while ((l_p = read(surowiec, bufor, MAX)) > 0){ // Odczytywanie MAX bajtów z deskryptora surowiec i umieszczanie je w buforze, aż do końca pliku
                write(filedes[1], bufor, l_p); // Zapisanie l_p bajtów z bufora do końca potoku do zapisu
                write(1, "Producent:", 10);
                write(1, bufor, l_p);       // } Wyświetlanie produktu == printf("Producent: %s \n", bufor);
                write(1, "\n", 1);
                sleep(rand() % 3); // Symulacja różnych szybkości działania programu
            }
            close(filedes[1]); // zamknięcie końca potoku do zapisu
            close(surowiec);
            write(1, "Producent zakończył działanie \n", 32); // printf("Producent zakończył działanie \n");
            break;
            
        default: ;// konsument
            int towar;
            int l_k; // liczba bajtów przeczytanych z potoku
            close(filedes[1]); // zamknięcie niużywanego końca potoku
            if ((towar = open("towar.txt", O_RDWR, O_CREAT, O_TRUNC)) == -1){ // Otwarcie pliku 'towar.txt' z flagą "otwórz plik do czytania i pisania", "jeśli nie istnieje to go stwórz", "Jeśli istnieje to go obetnij"
                perror("otwarcie towaru \n");
                exit(EXIT_FAILURE);
            }
            while ((l_k = read(filedes[0], bufor, MAX)) > 0){ // Odczytywanie MAX bajtów z końca potoku do odczytu
                write(towar, bufor, l_k); // Zapisz l_k bajtów z bufora do towaru
                write(1, "Konsument:", 10);
                write(1, bufor, l_k);       // } Wyświetlanie produktu == printf("Konsument:%s \n", bufor);
                write(1, "\n", 1);
                sleep(rand() % 3); // Symulacja różnych szybkości działania programu
            }
            close(towar);
            close(filedes[0]);
            write(1, "Konsument zakończył działanie \n", 32); // printf("Konsument zakończył działanie \n");
            break;
    };
}