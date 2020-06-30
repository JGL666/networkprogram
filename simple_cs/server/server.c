#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> 

#define SAFE_CLOSE_FD(fd) if(fd >= 0){close(fd);}
#define SEND_MSG "SERVER_MSG"
#define SEND_MSG_LEN sizeof(SEND_MSG)
int main(int argc, char **argv){
    int s_fd = -1;
    int c_fd = -1;
    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;
    char buf[32] = {0};
    int len = 0;
    socklen_t c_addr_len = 0;
    do{
       if(argc < 2){
            break;
       }

       if((s_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            break;
       }

       memset(&s_addr, 0, sizeof(s_addr));

       s_addr.sin_family = AF_INET;
       s_addr.sin_port = htons(atoi(argv[1]));
       s_addr.sin_addr.s_addr = INADDR_ANY;

       if(bind(s_fd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0){
            break;
       }

       if(listen(s_fd, 5) < 0){
            break;
       }
       
       memset(&c_addr, 0, sizeof(c_addr));

       //notice !!!
       c_addr_len = (socklen_t)sizeof(c_addr);
       if((c_fd = accept(s_fd, (struct sockaddr *)&c_addr, &c_addr_len)) < 0){
            break;
       }

       while(1){
            memset(buf, 0, sizeof(buf));

            if((len = read(c_fd, buf, sizeof(buf))) <= 0){
                break;
            }         

            printf("recv client -> %s\n", buf);

            if((len = write(c_fd, SEND_MSG, SEND_MSG_LEN)) <= 0){
                 break;
             }         
       }
       
    }while (0);

       
    SAFE_CLOSE_FD(s_fd)
    SAFE_CLOSE_FD(c_fd)
}
