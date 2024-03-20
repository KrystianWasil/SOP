#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>


int main() {
    
    if (fork() == 0) {
        creat("P1.txt",0666);
        creat("P2.txt",0666);
            if (fork() == 0) {
            int fd;
            char text[100];
               fd = open("P1.txt",O_WRONLY);
               fgets(text,100,stdin);
               fflush(stdin);
               write(fd,text,strlen(text));
               close(fd);
               exit(0);
            }
            wait(NULL);

            if (fork() == 0) {
                char text[100];
                int fd, copy_of_fd;
                fd = open("P1.txt",O_RDONLY);
                copy_of_fd = dup(fd);
                read(copy_of_fd,text,100);
                printf("\n%s",text);
                close(fd);
                close(copy_of_fd);
                exit(0);
            }
            wait(NULL);
            exit(0);
    }
    wait(NULL);
    if (fork()== 0) {
        char text[] = "Testzbitami10313431123";
        char test_text[100];
        int fd = open("P2.txt",O_RDWR);
        //test
        write(fd,text,23);
        lseek(fd,10,SEEK_SET);
        read(fd,test_text,20);
        printf("\n%s ",test_text);
        close(fd);
        if (fork() == 0) {
            char* arg[] = {"/bin/cp", "P1.txt", "P1kopia.txt", NULL};
            execv("/bin/cp",arg);
            exit(0);
        }
        wait(NULL);
        if (fork() == 0) {
            int check = access("P2.txt",R_OK);
            if (check == -1) {
                chmod("P2.txt",0444);
            }
            exit(0);
        }
        wait(NULL);
        exit(0);

    }
    wait(NULL);
    if (fork() == 0) {
        if (fork() == 0) {
            exit(0);
        }
        if (fork() == 0) {
            exit(0);
        }
        if (fork() == 0) {
            exit(0);
        }
        sleep(10);
    }

    return 0;
}
