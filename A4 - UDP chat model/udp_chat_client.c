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
    sock_id = socket(AF_INET , SOCK_DGRAM , 0);
    bzero(&servaddr , sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int len = sizeof(servaddr);

    // server to client and back
    bzero(recv_str , 100);
    bzero(send_str , 100);
    fgets(send_str , 100 , stdin);
    sendto(sock_id , send_str , strlen(send_str) , 0 , (struct sockaddr*) &servaddr , len);
    printf("Sending to server = %s" , send_str);
    recvfrom(sock_id , recv_str , 100 , 0 , (struct sockaddr*)&servaddr , &len);
    printf("server = %s" , recv_str);

    // client to server and back
    bzero(str , 100);
    recvfrom(sock_id , str , 100 , 0 , (struct sockaddr*)&servaddr , &len);
    printf("echoing back to server = %s" , str);
    sendto(sock_id , str , strlen(str) , 0 , (struct sockaddr*)&servaddr , len);
    printf("message sent to server\n");
}