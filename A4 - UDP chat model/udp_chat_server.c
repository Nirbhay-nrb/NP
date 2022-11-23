#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main(){
    char str[100];
    char recv_str[100];
    char send_str[100];
    int listen_id;
    struct sockaddr_in servaddr , clieaddr;

    listen_id = socket(AF_INET , SOCK_DGRAM , 0);
    bzero(&servaddr , sizeof(servaddr));
    bzero(&clieaddr , sizeof(clieaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int len = sizeof(clieaddr);

    bind(listen_id , (struct sockaddr*) &servaddr , sizeof(servaddr));
    // client to server and back
    bzero(str,100);
    recvfrom(listen_id , str , 100 , 0 , (struct sockaddr*)&clieaddr , &len);
    printf("echoing back to Client = %s" , str);
    sendto(listen_id , str , strlen(str) , 0 , (struct sockaddr*)&clieaddr , len);
    printf("message sent to client\n");

    // server to client and back
    bzero(recv_str,100);
    bzero(send_str,100);
    fgets(send_str , 100 , stdin);
    sendto(listen_id , send_str , strlen(send_str) , 0 , (struct sockaddr*)&clieaddr , len);
    printf("sending to client = %s" , send_str);
    recvfrom(listen_id , recv_str , 100 , 0 , (struct sockaddr*)&clieaddr , &len);
    printf("reply from client = %s" , recv_str);
}