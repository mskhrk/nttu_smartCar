//car_main3.c
//gcc -o car_main3 car_main3.c sm_car.c uart_setting.c treatWifi.c accident_decection.c carMove.c image_recognition.c -lpthread -lrt
/*common library*/
#include <stdio.h>
#include <stdlib.h>

/*pthread library*/
#include <pthread.h>

/*timer library*/
#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>        /* Definition of uint64_t */

/*error message*/
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

	
int Wifi_run=1;
int IR_run=1;
int IR_humanIdentification =1 ;
int IR_judgment =0 ;
int Wifi_fire=0,Wifi_mq3=0,Wifi_mq4=0;
int Wifi_mq7=0,Wifi_heart=0;
int Wifi_triaxialAccelerator=0;
char Wifi_fire_data[100];
char Wifi_mq3_data[100];
char Wifi_mq4_data[100];
char Wifi_mq7_data[100];
char Wifi_heart_data[100];
char Wifi_TriaxialAccelerator_data[100];
int CM_run=1; 
int CM_localFire;
int CM_localMq3;
int CM_localMq4;
int CM_localMq7;
int CM_localFall=1;
int CM_direction=2;
int CM_nowId=0;
int CM_maxId=0;
int CM_map_x=5000;
int CM_map_y=5000;
int CM_target=1;
int CM_secPointSize=50;
int CM_secPoint[50];
int CM_passPointSize=50;
int CM_passPoint[50];
int AD_nowRun;
	
void *threadFun1 (void *myvar);
void *threadFun2 (void *myvar);
void *threadFun3 (void *myvar);
void *threadFun4 (void *myvar);



int main(int argc, char *argv[])
{

pthread_t thread1,thread2,thread3,thread4;
char *msg1 = "accident_decection thread";
char *msg2 ="carMove thread";
char *msg3 ="image_recognition thread";
char *msg4 ="treatWifi thread";
int ret1,ret2,ret3,ret4;
int  main_map_buff[9]={0,0,0,0,0,0,0,0,0};


initArryay(CM_secPoint,CM_secPointSize);
initArryay(CM_passPoint,CM_passPointSize);

ret1 = pthread_create(&thread1,NULL,threadFun1, (void*) msg1);
ret2 = pthread_create(&thread2,NULL,threadFun2, (void*) msg2);
ret3 = pthread_create(&thread3,NULL,threadFun3, (void*) msg3);
ret4 = pthread_create(&thread4,NULL,threadFun4, (void*) msg4);

pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
pthread_join(thread3,NULL);
pthread_join(thread4,NULL);

//校正(設定)車子移動參數

//檢測目前位置與方位

if(CM_nowId==0){
	//掃描建立初始環境
	//預設id 1~10用於初始環境設定(目前使用1~4 5~10保留)
	initScanXY(5000,5000,1);//初始掃描id 1 初始北
	system("echo \"K1 90;\" > /dev/ttyPS1");//右順90
	CM_nowId=1;
	sleep(3);
	initScanXY(5000,5000,2);//初始掃描id 2 初始東
	system("echo \"K1 90;\" > /dev/ttyPS1");//右順90
	CM_nowId=2;
	sleep(3);
	initScanXY(5000,5000,3);//初始掃描id 3 初始南
	system("echo \"K1 90;\" > /dev/ttyPS1");//右順90
	CM_nowId=3;
	sleep(3);
	initScanXY(5000,5000,4);//初始掃描id 4 初始西
	CM_nowId=4;
	system("echo \"K1 90;\" > /dev/ttyPS1");//右順90
	sleep(3);
}
		

return 0;
}



void *threadFun1 (void *myvar)
{
	char *msg1;
	msg1 = (char*)myvar;
	accident_decection();
	return NULL;
}

void *threadFun2 (void *myvar)
{
	char *msg2;
	msg2 = (char*)myvar;
	carMove();
	return NULL;
}

void *threadFun3 (void *myvar)
{
	char *msg3;
	msg3 = (char*)myvar;
	//image_recognition();
	return NULL;
}

void *threadFun4 (void *myvar)
{
	char *msg4;
	msg4 = (char*)myvar;
	treatWifi();
	return NULL;
}

