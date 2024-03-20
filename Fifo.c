#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include <unistd.h>



int main() {
    mkfifo("HOTLINE",0600);
    int fdes;
    fdes = open("HOTLINE",O_RDWR);
    if (fdes == -1) {
        perror("aaa");
        exit(1);
    }
    char text[100];
    fgets(text,100,stdin);
    write(fdes,text,100);
return 0;
}
