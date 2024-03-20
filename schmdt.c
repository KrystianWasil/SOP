#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<string.h>
#include <sys/wait.h>


void reverse(char* text) {
    int len = strlen(text);
    int i, j;
    char temp;

    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = text[i];
        text[i] = text[j];
        text[j] = temp;
    }
}

int main() {
    int fdes;
    
    mkfifo("HOTLINE",0666);
    if (fork() == 0) {
        int shmid;
        char buff[100];
        char *buffer;
        fdes = open("HOTLINE",O_RDWR);
        shmid = shmget(45322,100,O_CREAT | 0666);
        if (shmid == -1) {
            perror("eeewee");
            exit(1);
        }
        read(fdes,buff,100);
        buffer = (char*)shmat(shmid,NULL,0);
        strcpy(buffer,buff);
        shmdt(&shmid);
        exit(0);
    }
    wait(NULL);
    char *buffer2;
    char text_to_reverse[100];
    int shmid2 = shmget(45321,100,0);
    buffer2 = shmat(shmid2,NULL,0);
    strcpy(text_to_reverse,buffer2);
    reverse(text_to_reverse);
    int fd2;
    printf("\n%s",text_to_reverse);
    fd2 = creat("abcd.txt",O_RDWR);
    fd2 = open("abcd.txt",O_WRONLY);
    write(fd2,text_to_reverse,100);
    close(fd2);

    shmdt(&shmid2);



    return 0;
}
