#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main(){
    int sock_id , n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;

    sock_id = socket(AF_INET , SOCK_STREAM , 0);
    bzero(&servaddr , sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_id , (struct sockaddr*)&servaddr , sizeof(servaddr));

    while(1){
        bzero(recvline , 100);
        bzero(sendline , 100);
        fgets(sendline , 100 , stdin);
        send(sock_id , sendline , strlen(sendline) , 0);
        recv(sock_id , recvline , 100 , 0);
        printf("Reply from server - %s" , recvline);
    }
}