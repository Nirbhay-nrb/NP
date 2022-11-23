#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main(){
    char msg[100];
    int sock_id;
    int enableBroadCast = 1;

    struct sockaddr_in servaddr , clieaddr;
    int len = sizeof(clieaddr);
    sock_id = socket(AF_INET , SOCK_DGRAM , 0);
    bzero(&servaddr , sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = INADDR_ANY;


    int res = setsockopt(sock_id , SOL_SOCKET , SO_REUSEADDR , &enableBroadCast , sizeof(enableBroadCast));
    printf("enabling broadcast options status = %d\n" , res);

    bind(sock_id , (struct sockaddr*)&servaddr , sizeof(servaddr));

    for(;;){
        bzero(&msg , sizeof(msg));
        recvfrom(sock_id , msg , 100 , 0 , (struct sockaddr*)&clieaddr , &len);
        printf("Received = %s" , msg);
    }  
}