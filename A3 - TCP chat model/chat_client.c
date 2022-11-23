#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main(){
    char str[100];
    char recv_str[100];
    char send_str[100];
    int sock_id;

    struct sockaddr_in servaddr;
    sock_id = socket(AF_INET , SOCK_STREAM , 0);
    bzero(&servaddr , sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_id , (struct sockaddr*)&servaddr , sizeof(servaddr));

    while(1){
        // client to server
        bzero(send_str , 100);
        bzero(recv_str , 100);
        fgets(send_str , 100 , stdin);
        send(sock_id , send_str , strlen(send_str) , 0);
        recv(sock_id , recv_str , 100 , 0);
        printf("Reply from server - %s" , recv_str);

        // server to client
        bzero(str,100);
        recv(sock_id , str , 100 , 0);
        printf("Echoing back to server - %s" , str);
        send(sock_id , str , strlen(str) , 0);
    }
}