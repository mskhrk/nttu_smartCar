	#include <stdio.h>	
	extern int IR_judgment;

	extern int Wifi_fire,Wifi_mq3,Wifi_mq4;
	extern int Wifi_mq7,Wifi_heart;
	extern int Wifi_triaxialAccelerator;
	
	extern int AD_nowRun;
	
	extern int CM_run; 
	extern int CM_localFire;
	extern int CM_localMq3;
	extern int CM_localMq4;
	extern int CM_localMq7;
	extern int CM_localFall;
	extern int CM_direction;
	extern int CM_nowId;
	extern int CM_secPoint;
	extern int CM_target;
	extern int CM_passPoint[50];


/*
	int AD_nowRun 0無移動 1跌倒移動 2意外移動(fire)
	int AD_nowRun 3意外移動(Mq3) 4意外移動(Mq4) 5意外移動(Mq7) 
	
	需預先設定這些點的位置
	int CM_localFire
	int CM_localMq3
	int CM_localMq4
	int CM_localMq7
	int CM_localFall
	
	int CM_direction;//面向方向
	int CM_nowId;
	int CM_target;
	
	int CM_secPoint[50];
	int CM_passPoint[50];//存放規劃路徑
	
*/
int carMove()
{
	int i_1;
	int step=-1; //計錄需求移動步數
	int CM_nowIdTem=CM_nowId;
	
	CM_passPoint[0]=CM_nowIdTem;//起始位置
	//計算移動路徑與移動
	while(1){
		if(CM_run==1)
		{
			//CM_passPoint[0]=0;//因路徑規劃運作需要所以至少要初始化第一筆
			do{
				CM_nowIdTem=findPath("hcar.map",CM_nowIdTem,CM_target,&CM_secPoint,CM_passPoint);//將計算結果放到CM_nowIdTem(一步一筆)
	
				for(i_1=49;i_1>=1;i_1--)//
				{
					CM_passPoint[i_1]=CM_passPoint[i_1-1];
				}
				step++;//未測試
				CM_passPoint[0]=CM_nowIdTem;
			}while(CM_nowIdTem!=0);
			
			//移動
			do{
			//CM_direction=goTarget("hcar.map",CM_direction,CM_nowId,CM_passPoint[step]);
			//CM_nowId=CM_passPoint[step];
			printf("CM_secPoint %d CM_nowId %d CM_passPoint[%d] %d\n",CM_secPoint,CM_nowId,step,CM_passPoint[step]);
			//sleep(3);
			step--;
			}while(step!=0);
			switch(AD_nowRun)
			{
				case 1:
				Wifi_fire=0;
				break;
				
				case 2:
				Wifi_mq3=0;
				break;
				
				case 3:
				Wifi_mq4=0;
				break;
				
				case 4:
				Wifi_mq7=0;
				break;
				
				case 5:
				Wifi_heart=0;
				break;
				
				case 6:
				Wifi_triaxialAccelerator=0;
				break;
				
				case 7:
				Wifi_triaxialAccelerator=0;
				IR_judgment=0;
				break;
			}
			CM_run=0;//移動結束
		}
	}
return 0;	
}
	

