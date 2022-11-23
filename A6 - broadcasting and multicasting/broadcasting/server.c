#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main(){ 
    char msg[100];
    int sock_id;
    struct sockaddr_in servaddr;
    
    sock_id = socket(AF_INET , SOCK_DGRAM , 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.255.255.255");

    int enableBroadCast = 1;
    int res = setsockopt(sock_id , SOL_SOCKET , SO_BROADCAST , &enableBroadCast , sizeof(enableBroadCast));
    printf("enabling broadcast options status = %d\n" , res);

    bind(sock_id , (struct sockaddr*) &servaddr , sizeof(servaddr));

    int len = sizeof(servaddr);
    
    for(;;){
        printf("Enter message to broadcast : ");
        bzero(&msg , sizeof(msg));
        fgets(msg , 100 , stdin);
        printf("Sending message : %s\n" , msg);
        sendto(sock_id , msg , strlen(msg) , 0 , (struct sockaddr*)&servaddr, len);
    }
}