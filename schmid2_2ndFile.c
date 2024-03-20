#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main() {
   const int MAX = 100;
    int shmid = shmget(45674, MAX*sizeof(int),0);
    if (shmid == -1) {
        perror("Creating shared memory");
        exit(1);
    }

    char *buff = (char*)shmat(shmid, NULL, 0);
    if (buff == NULL) {
        perror("Connecting shared memory");
        exit(1);
    }

    printf("Enter two values: ");
    scanf("%c %c", buff + 2, buff + 3);

    shmdt(buff);

    return 0;
}
