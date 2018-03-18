//gcc -o client ./Client2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void getMessage(char*);
int main(int argc , char *argv[])
{
    char m[100]={};
	while(1)
	{
	getMessage(m);
	sleep(3);
	}

    return 0;
}

void getMessage(char *message )
{
	//socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //連線到主機
    info.sin_addr.s_addr = inet_addr("192.168.0.123");
    info.sin_port = htons(12345);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
    }
	
	//Send a message to server
    //char message[] = {"Hi there"};
    char receiveMessage[100] = {};
    //send(sockfd,message,sizeof(message),0);
    recv(sockfd,receiveMessage,sizeof(receiveMessage),0);

    printf("%s\n",receiveMessage);
    printf("close Socket\n");
    close(sockfd);
}