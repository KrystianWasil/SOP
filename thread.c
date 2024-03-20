#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

#define MAX 100


//mialem tutaj problem z uprawnieniami zadna kombinacja nie 
//pozwalala mi ustawic wartosc np do odczytu i zapisui musze to robic reczenie w plikach
//w kolejnej czesci zadania to widac kiedy program sprawdza czy mam uprawnienia czy ich nie ma

//funkcja wyjatku
void *threadFunction(void *arg) {
    char *text = (char *)arg;
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = toupper(text[i]);
    }

    printf("Result: %s\n", text);

    return NULL;
}

int main() {
    char text[1024];
    int o;
    if (mkdir("Katalog1", 0777) == -1) { 
        perror("dictionary not created!");
        exit(1);
    } 
    o = open("/home/vboxuser/Desktop/vsc/Katalog1/plik1.txt",O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (mkdir("Katalog2", 0777) == -1) {
        perror("dictionary not created!");
        exit(1);
    } else {
        printf("All fine\n");
        }
    

    int shmid;
    char *buffer;
    shmid = shmget(74543, MAX * sizeof(char), IPC_CREAT | 0600);
    if (shmid == -1) {
        perror("Failed to create shared memory");
        exit(1);
    }

    buffer = (char *)shmat(shmid, NULL, 0);
    if (buffer == NULL) {
        perror("Failed to attach shared memory");
        exit(1);
    }

    strcpy(buffer, "Lets gooo");

    printf("Shared memory content: %s\n", buffer);
    if (o == -1) {
        perror("Failed to open file");
        exit(1);
    }
    //tutaj zapisuje do pliku 
    write(o, buffer, strlen(buffer));
    close(o);

    printf("Enter text: ");
    fgets(text, sizeof(text) - 1, stdin);

    pthread_t myThread;

    if (pthread_create(&myThread, NULL, threadFunction, (void *)text)) {
        perror("Failed to create thread");
        exit(1);
    }

    if (pthread_join(myThread, NULL)) {
        perror("Failed to join thread");
        exit(1);
    }

    const char *file1 = "/home/vboxuser/Desktop/vsc/Katalog1/plik1.txt";
    int test = access(file1, R_OK | W_OK | X_OK);
    if (test == -1) {
        perror("No permissions");
        int chmod_ = chmod(file1, S_IRUSR | S_IWUSR | S_IXUSR);
        if (chmod_ == -1) {
            perror("Failed to change permissions");
            return 0;
        }
    } else {
        printf("Has permissions\n");
        int chmod_ = chmod(file1, S_IRUSR | S_IXUSR);
        if (chmod_ == -1) {
            perror("Failed to change permissions");
            return 1;
        }
    }
    // sprawdzam czy ta funkcja dziala z usuwaniem plikow 
    int DictionaryRemoveTest1 = remove("/home/vboxuser/Desktop/vsc/Katalog1");
    if (DictionaryRemoveTest1 != -1) {
        printf("TEST SUCCEEDED\n");
    } else {
        perror("Failed");
    }

    int trashBin = remove(file1);
    if (trashBin == -1) {
        perror("Failed to delete file");
    } else {
        printf("All fine\n");
    }
    // te dwa "testy" sa rozdzielone zabym wiedzial czy dziala  z niepustym i pustym

    int DictionaryRemoveTest2 = remove("/home/vboxuser/Desktop/vsc/Katalog2");
   
    if (DictionaryRemoveTest2 != -1) {
        printf("TEST SUCCEEDED\n");
    } else {
        perror("Failed");
    }
    // chyba nie dziala na niepsuty folder :(

    shmdt(buffer); // gdy czytalem o pamieci wspoldzielonej uznalem ze podobnie jak z alokacja trzeba to zwolnic ale nie wiem czy to dobra analogia
                   // odlaczam pramiec wspoldzielona tutaj!


    return 0;
}
