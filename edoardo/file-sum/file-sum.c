#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
extern int errno;
int main(int argc, char * argv[]){
    if(argc <= 1) return -1;
    char* dir = argv[1];
    char* stringa = "Ciao a tutti";
    int fd = open(dir, O_RDONLY);

    printf("fd = %d\n", fd);
    if(errno == ENOENT){
        fd = open(dir, O_WRONLY|O_CREAT);
        write(fd, stringa, strlen(stringa));
        close(fd);
    }

    fd = open(dir, O_RDONLY);
    unsigned char buf[100];
    int nRead;
    int res = 0;
    do{
        nRead=read(fd, buf, sizeof(buf));
        int i;
        for(i = 0; i < nRead; i++){
            res=(res+buf[i])%256;
//            printf("%c\n",  putc(buf[i], stdout));
            putc(buf[i], stdout);
        }
    }while(nRead!=0 && nRead!=-1);

    /*PRINT RES AND CLOSE*/
    printf("La somma è: %d", res);
    close(fd);
    return 0;
}