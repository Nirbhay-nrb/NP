#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main(){
    char str[100];
    char revstr[100];
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
    printf("From client = %s" , str);
    int slen = strlen(str);
    for(int i=0 ; i<slen ; i++){
    	revstr[i] = str[slen-i-1];
    	if(i==(slen-1)){
    		printf("Echoing back to Client = %s \n" , revstr);
    	}
    }
    sendto(listen_id , revstr , strlen(revstr) , 0 , (struct sockaddr*)&clieaddr , len);
    printf("message sent to client\n");
}
