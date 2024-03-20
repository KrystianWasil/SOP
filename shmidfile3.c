#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>



int main() {
    const int MAX = 100;
    int shmid = shmget(45674, MAX*sizeof(int), 0);
    if (shmid == -1) {
        perror("Creating shared memory");
        exit(1);
    }

    char *buff = (char *)shmat(shmid, NULL, 0);
    if (buff == NULL) {
        perror("Connecting shared memory");
        exit(1);
    }
    //tutah sa tablica na inty coutner i suma
    int arr[10] = {0};
    int j = 0;
    int sum = 0;
    printf("Shared Memory iside:\n");
    for (int i = 0; i < 4; i++) {
        printf("%c\n",buff[i]);
        if (buff[i] >= '0' && buff[i] <= '9') {
            arr[j] = buff[i] - '0';
            j++;
        }
    }
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }

    printf("\nSum : %d", sum);

    shmdt(buff);
   
}
