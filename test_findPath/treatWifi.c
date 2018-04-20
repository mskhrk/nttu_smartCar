#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

	extern int Wifi_run;
	extern int Wifi_fire; 
	extern char Wifi_fire_data[100];
	extern int Wifi_mq3;
	extern char Wifi_mq3_data[100];
	extern int Wifi_mq4;
	extern char Wifi_mq4_data[100];
	extern int Wifi_mq7;
	extern char Wifi_mq7_data[100];
	extern int Wifi_heart;
	extern char Wifi_heart_data[100];
	extern int Wifi_triaxialAccelerator;
	extern char Wifi_TriaxialAccelerator_data[100];

	void getMessage(char* ,char*);
	void checkData(char*,int*);
	
/*	全域變數
	
	Wifi_run 1/0 是否執行wifi執行緒
	Wifi_fire 1/0 是否發生火災 有異常為1
	Wifi_fire_data char[100] 接收資料空間
	Wifi_mq3 1/0
	Wifi_mq3_data char[100]
	Wifi_mq4 1/0
	Wifi_mq4_data char[100]
	Wifi_mq7 1/0
	Wifi_mq7_data char[100]
	Wifi_heart 1/0
	Wifi_heart_data char[100]
	Wifi_triaxialAccelerator 1/0
	Wifi_TriaxialAccelerator_data char[100]
*/
int treatWifi()
{
	while(1){
		if(Wifi_run==1)
		{
			getMessage(Wifi_fire_data,"192.168.0.11");
			getMessage(Wifi_mq3_data,"192.168.0.13");
			getMessage(Wifi_mq4_data,"192.168.0.14");
			getMessage(Wifi_mq7_data,"192.168.0.17");
			getMessage(Wifi_heart_data,"192.168.0.21");
			getMessage(Wifi_TriaxialAccelerator_data,"192.168.0.22");
			checkData(Wifi_fire_data,&Wifi_fire);
			checkData(Wifi_mq3_data,&Wifi_mq3);
			checkData(Wifi_mq4_data,&Wifi_mq4);
			checkData(Wifi_mq7_data,&Wifi_mq7);
			checkData(Wifi_heart_data,&Wifi_heart);
			checkData(Wifi_TriaxialAccelerator_data,&Wifi_triaxialAccelerator);
		}
	}
return 0;
}


void getMessage(char *message ,char *ip)
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
    //info.sin_addr.s_addr = inet_addr("192.168.0.123");
	info.sin_addr.s_addr = inet_addr(ip);
    info.sin_port = htons(12345);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
    }
	
	
	recv(sockfd,message,sizeof(message),0);
	//Send a message to server
    //char message[] = {"Hi there"};
    //char receiveMessage[100] = {};
    //send(sockfd,message,sizeof(message),0);
    //recv(sockfd,receiveMessage,sizeof(receiveMessage),0);

    //printf("%s\n",receiveMessage);
    //printf("close Socket\n");
    close(sockfd);
}
void checkData(char *data,int *status){
	if(data[0]=='a'){status[0]=1;}
}