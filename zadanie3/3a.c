#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void my_signal_handler(int);

int main(int argc, char *argv[]){
    if (argc < 3){ // sprawdzenie argumentów wywołania programu
        printf("Usage: make run1 met={metoda} num={numer sygnału}\n");
        printf("**Dostępne metody: \n1. ignoruj \n2. przechwyc \nkazda inna metoda będzie traktowana jako wykonanie operacji domyślnej dla sygnału jednak jakakolwiek metoda musi być podana \n");
        printf("**Numer sygnału dla którego będzie wykonywana metoda.\n");
        exit(1);
    }
    int numer_sygnalu = atoi(argv[2]); // numer sygnału
    char *metoda = argv[1]; // zmienna zawierająca przekazaną metodę
    printf("Proces o PID: %d czeka na przekazanie sygnału... \n", getpid());
    // OBSŁUGA SYGNAŁU
    if (strcmp(metoda, "ignoruj") == 0){ // ignorowanie sygnału zgodnie z podaną metodą
        if (signal(numer_sygnalu, SIG_IGN) == SIG_ERR){  // ignorowanie sygnału
            perror("Funkcja signal ma probelm z ignorowaniem sygnału \n");
            exit(EXIT_FAILURE);
        }
    }
    if (strcmp(metoda, "przechwyc") == 0){ // przechwytywanie sygnału
        if (signal(numer_sygnalu, my_signal_handler) == SIG_ERR){  // przechwytywanie sygnału i wykonywanie operacji zdefiniowanej w my_signal_handler
            perror("Funkcja signal ma probelm z ignorowaniem sygnału \n");
            exit(EXIT_FAILURE);
        }
    }
    pause(); // program czeka na otrzymanie sygnału
}

void my_signal_handler(int s){ //   Własna obsługa sygnału
    printf("Sygnał został przechwycony :)\n");
}



