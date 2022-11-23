#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main(){
    char str[100];
    char recv_str[100];
    char send_str[100];
    int listen_id, comm_id;

    struct sockaddr_in servaddr;
    listen_id = socket(AF_INET , SOCK_STREAM , 0);
    bzero(&servaddr , sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listen_id , (struct sockaddr*)&servaddr , sizeof(servaddr));
    listen(listen_id , 5);

    while(1){
        comm_id = accept(listen_id , (struct sockaddr*)NULL , NULL);
        // client to server
        bzero(str,100);
        recv(comm_id , str , 100 , 0);
        printf("Echoing back - %s" , str);
        send(comm_id , str , strlen(str) , 0);

        // server to client
        bzero(recv_str , 100);
        bzero(send_str , 100);
        fgets(send_str , 100 , stdin);
        send(comm_id , send_str , strlen(send_str) , 0);
        recv(comm_id , recv_str , 100 , 0);
        printf("Reply from client = %s" , recv_str);
        close(comm_id);
    }
}