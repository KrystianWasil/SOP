#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>


// nie wiem czy w tym zadaniu jest inna opcja niz wpisywanie charow a potem zamiienianie je na int ale chyba o to chodizlo 
// itez nie wiem co w koncu wpisywac w te perror bo u Pani w pliakch jest np : utworzenie pamieci wspoldzielonej a m sie wydaje ze tam powinna byc tresc bledu
// ale robie tak jak u Pani w pliku;
int main() {
    const int MAX = 100;
    int shmid;
    shmid = shmget(45674, MAX*sizeof(int), IPC_CREAT | 0600);
    if (shmid == -1){
        perror("Creating shared memory");
        exit(1);
    }
    char *buff = (char *)shmat(shmid, NULL, 0);
    if (buff == NULL) {
        perror("Connecting shared memory");
        exit(1);
    }

    printf("Enter two values: ");
    scanf("%c %c", buff, buff + 1);

    shmdt(buff);

    return 0;
        
}
