#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h> 

#define SAFE_CLOSE_FD(fd) if(fd >= 0){close(fd);}
#define SEND_MSG "CLIENT_MSG"
#define SEND_MSG_LEN sizeof(SEND_MSG)

int main(int argc, char **argv){
    int c_fd = -1;
    struct sockaddr_in s_addr;
    char buf[32] = {0};
    
    do{
        if(argc < 3){
            break;
        }

        if((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
             break;
        }

        memset(&s_addr, 0, sizeof(s_addr));
        s_addr.sin_family = AF_INET;
        s_addr.sin_port = htons(atoi(argv[2]));
        s_addr.sin_addr.s_addr = inet_addr(argv[1]);

        if(connect(c_fd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0){
            break;
        }

        while(1){
            if(write(c_fd, SEND_MSG, SEND_MSG_LEN) <= 0){
                break;
            }

            memset(buf, 0, sizeof(buf));

            if(read(c_fd, buf, sizeof(buf)) <= 0){
                break;
            }

            printf("recv server: %s\n", buf);

	    sleep(1);
        }
    }while(0);

    SAFE_CLOSE_FD(c_fd)
}
