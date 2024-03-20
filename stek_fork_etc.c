#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main() {
    int pid1, pid2, pid3;
    int file1, file2;

    // Pierwszy potomek
    pid1 = fork(); 
    if (pid1 == -1) {
        perror("Sth wrong");
        exit(1);
    } else if(pid1 == 0) {
        file1 = open("plik1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (file1 == -1) {
            perror("Sth wrong");
            exit(1);
        } else {
            char text[1024];
            printf("Wpisz tekst dla procesu 1: ");
            fgets(text, sizeof(text), stdin);
            write(file1, text, strlen(text));
        }
        close(file1);
        printf("Proces 1 zakończył zapisywanie do pliku\n");
        exit(0);
    }

    // Drugi potomek
    pid2 = fork(); 
    if (pid2 == -1) {
        perror("Sth wrong");
        exit(1);
    } else if(pid2 == 0) {
        file2 = open("plik2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (file2 == -1) {
            perror("Sth wrong");
            exit(1);
        } else {
            char text[1024];
            printf("Wpisz tekst dla procesu 2: ");
            fgets(text, sizeof(text), stdin);
            write(file2, text, strlen(text));
        }
        close(file2);
        printf("Proces 2 zakończył zapisywanie do pliku\n");
        exit(0);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // Trzeci potomek
    pid3 = fork();
    if (pid3 == -1) {
        perror("Sth wrong");
        exit(1);
    } else if (pid3 == 0) {
        int counter = 0;
        file1 = open("plik1.txt", O_RDONLY);
        if (file1 == -1) {
            perror("Sth wrong");
            exit(1);
        }
        
        char buffer[1024];
        
        lseek(file1, 0, SEEK_SET);
        while (read(file1, buffer, 1) != '\0') {
            counter ++;
        }
        
        close(file1);

        file2 = open("plik2.txt", O_RDONLY);
        if (file2 == -1) {
            perror("open");
            exit(1);
        }
        lseek(file2, 0, SEEK_SET);
        while (read(file2, buffer,1) != '\0') {
            counter++;
        }
        
       
        
        close(file2);
        counter = counter-2; // minus 2 bo znaki koncowe a juz nie wiem jak sie tego pozbyc 
    
        printf("Liczba znaków w plikach: %d\n", counter);
        exit(0);
    }
    
    wait(NULL);

    return 0;
}

